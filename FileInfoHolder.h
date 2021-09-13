
class FileInfoHolder{
    public:
            int deleted;
            int modified;
            int items;
            int base;
            int T;
            int A;
            FileInfoHolder();
            FileInfoHolder(int deleted, int modified, int items, int base, int T,int A);
};

//.i
FileInfoHolder::FileInfoHolder(){
    this->deleted = 0;
    this->modified = 0;
    this->items = 0;
    this->base = 0;
    this->T = 0;
    this->A = 0;
}

//.i
FileInfoHolder::FileInfoHolder(int deleted, int modified, int items, int base, int T, int A){
    this->deleted = deleted;
    this->modified = modified;
    this->items = items;
    this->base = base;
    this->T = T;
    this->A = A;
}