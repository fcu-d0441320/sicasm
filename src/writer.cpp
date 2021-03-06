#include"writer.hpp"

writer::writer(string ListFileName,string objFileName,bool is_Upper){
    this->ObjFile.open(objFileName,ios::out);
    this->ListFile.open(ListFileName,ios::out);
    this->initList();
    this->stopOBJFILE=false;
    this->is_Upper=is_Upper;
}
writer::~writer(){
    this->ListFile.close();
    this->ObjFile.close();
    this->ByteCounter = 0;
    this->CardContentBuff="";
    this->CardType = ' ';
    this->startLoc=0;
}
string writer::toUpper(string from){
    for(unsigned int i=0;i<from.length();i++){
        from.at(i)=toupper(from.at(i));
    }
    return from;
}
void writer::outputHCard(string ProgramName,unsigned int startAddress,unsigned int endAddress){
    if(this->stopOBJFILE)return;
    if(ProgramName.length()>6)this->ObjFile<<"H"<<ProgramName.substr(0,6);
    else{
        this->ObjFile<<"H"<<ProgramName;
        for(unsigned int i=0;i<6-ProgramName.length();i++)this->ObjFile<<" ";
        if(this->is_Upper)this->ObjFile<<uppercase;
        this->ObjFile<<setw(6)<<setfill('0')<<hex<<startAddress;
        this->ObjFile<<setw(6)<<setfill('0')<<(endAddress-startAddress)<<setw(0)<<setfill(' ')<<dec<<endl;
    }
}

void writer::outputECard(unsigned int mainAddress){
    if(this->stopOBJFILE)return;
    this->writeTCard();
    if(this->is_Upper)this->ObjFile<<uppercase;
    this->ObjFile<<"E"<<hex<<setw(6)<<setfill('0')<<mainAddress<<dec<<setw(0)<<setfill(' ');
}
void writer::outputList(AsmCode*data){
    string outTxt =data->toString();
    this->ListFile<<outTxt<<endl;
    data->printErrMes(this->ListFile);
}
void writer::outputTCard(unsigned int address,string data){
    if(this->stopOBJFILE)return;
    if(this->CardContentBuff.length()==0){
        this->ByteCounter=0;
        this->startLoc = address;
    }

    if(this->ByteCounter+data.length()/2>30){
        this->writeTCard();
        this->startLoc = address;
    }
    this->CardContentBuff = this->CardContentBuff + data.substr(0,data.length()/2*2);
    this->ByteCounter += data.length()/2;
}
void writer::writeTCard(){
    if(this->stopOBJFILE)return;
    if(this->ByteCounter==0);
    else{
        if(this->is_Upper)this->ObjFile<<uppercase;
        this->ObjFile<<"T";
        this->ObjFile<<hex<<setw(6)<<setfill('0')<<this->startLoc;
        this->ObjFile<<hex<<setw(2)<<setfill('0')<<this->ByteCounter<<dec<<setw(0)<<setfill(' ');
        if(this->is_Upper)this->CardContentBuff=this->toUpper(this->CardContentBuff);
        this->ObjFile<<this->CardContentBuff<<endl;
        this->ByteCounter=0;
        this->CardContentBuff="";
        this->startLoc=0;
    }
}
void writer::initList(){
    this->ListFile<<"Sic Assamber v1.2 Made By Dream Rhythm"<<endl;
    this->ListFile<<"Line   Loc   obj     Label   OPCode  Data      comment"<<endl;
    this->ListFile<<"====   ====  ======  ======  ======  ========  =========================="<<endl;
}
void writer::stopOutputObjFILE(bool setting){
    this->stopOBJFILE=setting;
}
