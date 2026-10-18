#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
class Restaurant{
    private:
        const int id;
        string denumire;
        int nrMese;
        float* vectorPreturiMeniuri;
    public:
        static int nr_restaurante;
        Restaurant() : id(++nr_restaurante)
        {
            this->denumire = "Restaurant";
            this->nrMese =0;
            this->vectorPreturiMeniuri=nullptr;
        }
        Restaurant(int id, string denumire, int nrMese, float* vectorPreturiMeniuri):id(id)
        {
            this->denumire=denumire;
            this->nrMese=nrMese;
            if(nrMese > 0 && vectorPreturiMeniuri != nullptr )
            {
                this->vectorPreturiMeniuri = new float[nrMese];
                for(int i=0; i<this->nrMese; i++)
                {
                    this->vectorPreturiMeniuri[i]=vectorPreturiMeniuri[i];
                }
            }else
            {
                this->vectorPreturiMeniuri= nullptr;
                this->nrMese=0;
            }
            nr_restaurante++;
        }
        ~Restaurant()
        {
            if(this->vectorPreturiMeniuri != nullptr)
            {
                delete[] this-> vectorPreturiMeniuri;
            }
        }
        void afisare()
        {
            cout<<"Restaurant ID: " << id<< endl;
            cout<<"Denumire: "<< denumire<< endl;
            cout<<"Nr mese: "<< nrMese<< endl;
            if(nrMese >0 && vectorPreturiMeniuri != nullptr)
            {
                cout<< "Preturi meniuri: ";
                for(int i=0; i<nrMese; i++)
                    cout<<vectorPreturiMeniuri[i]<< " ";
                cout<<endl;
            }
            
        }
    };
        int Restaurant::nr_restaurante=0;
        int main()
        {
         Restaurant r1;
         r1.afisare();
         float preturi[]={45.5,60.0,35.0,120.5};
         Restaurant r2(10,"Lake House",4,preturi);
         r2.afisare();
         return 0;
        }
