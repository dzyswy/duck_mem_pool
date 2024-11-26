#include "user/person.h"



using namespace duck::user;

const int max_size = 16;

int main(int argc, char* argv[])
{
    google::InstallFailureSignalHandler();
    google::InitGoogleLogging(argv[0]);


    FLAGS_stderrthreshold = 0;
    FLAGS_minloglevel = 0;


    PersonPool person_pool(18, "tom", 8, 4, 128);
    Person* buff[max_size] = {nullptr};

    for (int i = 0; i < max_size; i++) {
        buff[i] = person_pool.get();
        buff[i]->set_age(i);
    }
    
    for (int i = 0; i < max_size; i++) {
        printf("%d: age=%d\n", i, buff[i]->age());
    }

    for (int i = 0; i < max_size; i++) {
        person_pool.put(&buff[i]); 
    }

    for (int i = 0; i < max_size; i++) {
        printf("%d: ptr=%p\n", i, buff[i]);
    }

    for (int i = 0; i < max_size; i++) {
        buff[i] = person_pool.get(); 
    }

    for (int i = 0; i < max_size; i++) {
        printf("%d: age=%d\n", i, buff[i]->age());
    }

    std::cout << "wait key..." << std::endl;
    std::getchar();  

    std::cout << "bye!" << std::endl;



    return 0;
}




