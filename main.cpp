#define CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

struct Student{
    char surname[20];
    int marks[3];
};

void check_fin(std::ifstream& fin){
    if(!fin.good()) throw "file isn't exist";
    if(!fin) throw "file open error";
    if(fin.peek()==EOF) throw "file is empty";
}

void check_fout(std::ofstream& fout){
    if(!fout) throw "file open error";
}

void CreateBin(const char* filepass){
    std::ofstream fout_bin("file.bin", std::ios::binary | std::ios::app);
    std::ifstream fin_txt(filepass);
    
    check_fin(fin_txt);

    Student student;
    std::string delims, buff, sur_name;
    size_t beg, end;

    std::getline(fin_txt, delims);
    while(std::getline(fin_txt, buff)){
        beg=buff.find_first_not_of(delims);

        if(beg!=std::string::npos){
            end=buff.find_first_of(delims);

            if(end=std::string::npos){
                    end=buff.length();
            }
                
            strcpy(student.surname, buff.substr(beg, end-beg).c_str());
                
            beg=buff.find_first_of(delims);
            for(int i=0;i<3;++i){
                end=buff.find_first_not_of(delims);
                    
                if(beg!=std::string::npos){
                    end=buff.find_first_of(delims);

                    if(end!=std::string::npos){
                        end=buff.length();
                    }

                student.marks[i]=std::stoi(buff.substr(beg, end-beg)); 

                }
            }
        }
        fout_bin.write(reinterpret_cast<char*>(&student), sizeof(Student));
    }
    fout_bin.close();
}
void ReadBin(const std::string& filepass){
    std::ifstream fin(filepass, std::ios::binary);
    check_fin(fin);
    Student student;

    for(int i=0;i<3;++i){
        fin.read(student.surname, sizeof(student.surname));
        fin.read((char*)student.marks, sizeof(student.marks));
        std::cout<<student.surname<<' ';
        for(int i=0;i<3;++i){
            std::cout<<student.marks[i]<<' ';
        }
        std::cout<<'\n';
    }
}

int main(){
    try{
    CreateBin("in.txt");
    ReadBin("file.bin");
    }catch(const char* error_msg){
        std::cout<<error_msg;
    }


    

    return 0;
}
//дз: прочитать бинарный файл и вывести результат в консоль. Поменять местами 1 и предпоследнего студента в файле.