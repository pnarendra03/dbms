#include<bits/stdc++.h>
using namespace std;

int maxsize=0;
class bucket{
    public:
    int local_depth;
    vector <int > data;
    bucket(int b){
        this->local_depth=b;
    }
    bool is_empty();
    void split_bucket(int x);
    void merge_bucket(int x);
    
};
class directory{
    public:
    int global_depth;
    map<int, bucket*>buckets;
    int hash_function(int x);
    void insertion(int x);
    void deletion(int x);
    directory(int gd){
        this->global_depth=gd;
    }
    void directory_expand();
    void directory_shrink();
    void display_directory();
};

void directory::display_directory(){
    cout<<endl;
    for(auto it:buckets) {
        cout<<it.first<<" - ";
        for(auto buc:it.second->data) {
            cout<<buc<<" ";
        }
        cout<<" - "<<it.second->local_depth<<endl;
    }

}

int directory::hash_function(int x){
    return x &((1<<global_depth)-1);
}

void directory::deletion(int val) {
    int bucket_number = hash_function(val);
    bucket* b =buckets[bucket_number];
    auto it  = find(b->data.begin(),b->data.end(),val);
    if(it!=b->data.end()) {
        cout<<"Element not found\n";
        return;
    }
    b->data.erase(it);
    int bucket_number2;
    if(bucket_number<(1<<(global_depth-1))) {
        bucket_number2 = bucket_number+1<<(global_depth-1);
    }
    else {
        bucket_number2 = bucket_number - 1<<(global_depth-1);
    }
    bucket* b2 = buckets[bucket_number2];
    if(b2!=b) {
        if(b->data.size()+b2->data.size()>maxsize) {
            return;
        }
        for(auto it:b2->data) {
            b->data.push_back(it);
        }
        b2->data.clear();
        b->local_depth--;
        buckets[bucket_number2] = b;
        
        free(b2);

        int maxLocDepth = 0;
        for(auto it : buckets) {
            maxLocDepth = max(maxLocDepth,it.second->local_depth);
        }
        auto it = buckets.find(1<<maxLocDepth);
        buckets.erase(it,buckets.end());

    }

}

void directory::insertion(int x){
    
    int bucket_number = hash_function(x);
    // -----------------------
    bucket * b2 = buckets[bucket_number];
    // -----------------------
    if(buckets[bucket_number]->data.size()<maxsize) {
        buckets[bucket_number]->data.push_back(x);
        return;
    }
    if(buckets[bucket_number]->local_depth<global_depth) {
        buckets[bucket_number]->local_depth++;
        bucket * b1 = new bucket(buckets[bucket_number]->local_depth);
        //--------------------
        vector<int> indices;
        for(auto it:buckets) {
            if(it.second == b2) {
                indices.push_back(it.first);
            }
        }
        for(int ek=indices.size()/2;ek<indices.size();ek++){
            buckets[ek]=b1;
        }
        indices.clear();
        for(auto it:b2->data) {
            indices.push_back(it);
        }
        buckets[bucket_number]->data.clear();
        for(int i=0;i<indices.size();i++) {
            int b_number = hash_function(indices[i]);
            buckets[b_number]->data.push_back(indices[i]);
        }
        int b_number = hash_function(x);
        // buckets[b_number]->data.clear();
        buckets[b_number]->data.push_back(x);
    }
    else {
        global_depth++;
        buckets[bucket_number]->local_depth++;
        bucket * b1 = new bucket(buckets[bucket_number]->local_depth);
        for(int i=1<<(global_depth-1);i<(1<<(global_depth));i++) {
            buckets[i] = buckets[i-(1<<(global_depth-1))];
        }
        vector<int> indices;
        for(auto it:buckets) {
            if(it.second == b2) {
                indices.push_back(it.first);
            }
        }
        for(int ek=indices.size()/2;ek<indices.size();ek++){
            buckets[ek]=b1;
        }
        indices.clear();
        for(auto it:b2->data) {
            indices.push_back(it);
        }
        for(int i=0;i<indices.size();i++) {
            int b_number = hash_function(indices[i]);
            buckets[b_number]->data.push_back(indices[i]);
        }
        int b_number = hash_function(x);
        buckets[b_number]->data.push_back(x);
    }


}

int main(){
    cout<<"Enter the bucket capacity:\n";
    cin>>maxsize;
    cout  << "enter 1 to insert \n";
    cout  << "enter 2 to delete \n";
    cout  << "enter 3 to search \n";
    cout  << "enter 4 to print \n";
    int n;
    directory* d = new directory(0);
    bucket* b = new bucket(0);
    d->buckets.insert({0,b});
    // d->global_depth = 1;
    int value;
    while(1){
        cin >> n;
        switch (n){
            case 1:{
                cout << "insert the value that is to be inserted ";
                cin >> value;
                d->insertion(value);
                break;
            }
            case 2:{
                cout << "enter the number that is to be deleted ";
                cin >> value ;
                d->deletion(value);
                break;
            }
            case 4:{
                cout << "enter the number that is to be find";
                d->display_directory();
                break;
            }
            default:{
                cout << "invalid choice. Please enter a valid choice";
            }
    
    
        }
    }
   
}



/*
Written By->
Name : Narendra Kumar 
Roll Number: 20074022
Branch : Computer Science and engineering
Institute : Indian Institute of technology (BHU), Varanasi.
*/