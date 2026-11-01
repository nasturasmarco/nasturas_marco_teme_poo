#include <bits/stdc++.h>
using namespace std;
//enum TipCombustibil {
    //BENZINA,
    //MOTORINA,
    //ELECTRIC,
    //HIBRID,
//}
class Masina
{
    private:
        const int idMasina;
        string model;
        int nrRevizii;
        float* istoricConsum;
    public:
        static int nrMasini;
        Masina() : idMasina(++nrMasini)
        {
            this->model="Default";
            this->nrRevizii=0;
            this->istoricConsum =nullptr;
        }
        Masina(int idMasina, string model, int nrRevizii, float* istoricConsum)
            : idMasina(idMasina)
            {
                this->model=model;
                this->nrRevizii=nrRevizii;
                if(nrRevizii>0 && istoricConsum!=nullptr)
                {
                    this->istoricConsum=new float[nrRevizii];
                    for(int i=0; i<this->nrRevizii; i++)
                        this->istoricConsum[i]=istoricConsum[i];
                }
                else
                {
                    this->nrRevizii=0;
                    this->istoricConsum=nullptr;
                }
                nrMasini++;
            }
            ///constructor de copiere
            Masina(const Masina& m) : idMasina(++nrMasini)
            {
                this->model=m.model;
                this->nrRevizii=m.nrRevizii;
                if(m.istoricConsum!=nullptr && m.nrRevizii>0)
                {
                    this->istoricConsum=new float[m.nrRevizii];
                    for(int i=0; i<m.nrRevizii; i++)
                        this->istoricConsum[i]=m.istoricConsum[i];
                }
                else
                    this->istoricConsum=nullptr;
            }
            Masina& operator=(const Masina& m)
            {
                if(this==&m)
                    return *this;
                this->model=m.model;
                this->nrRevizii=m.nrRevizii;
                if(this->istoricConsum!=nullptr)
                {
                    delete[] this->istoricConsum;
                    this->istoricConsum=nullptr;
                }
                if(m.istoricConsum!=nullptr && m.nrRevizii>0)
                {
                    this->istoricConsum=new float[m.nrRevizii];
                    for(int i=0; i<m.nrRevizii; i++)
                        this->istoricConsum[i]=m.istoricConsum[i];
                }
                else
                    this->istoricConsum=nullptr;
                return *this;
            }
            void afisareMasina()
            {
                cout<<endl<<"Id masina: "<<this->idMasina;
                cout << endl << "Model: " << this->model;
		        cout << endl << "Nr revizii: " << this->nrRevizii;
		        if(this->nrRevizii >0 && this->istoricConsum!=nullptr)
		        {
		            cout<<endl<<"Istoric consum (l/100km): ";
		            for(int i=0; i<this->nrRevizii-1; i++)
		                cout<<this->istoricConsum[i]<<",";
		          cout<<this->istoricConsum[this->nrRevizii-1]<<".";
		        }
		            
            }
            int getNrRevizii()
            {
                return this->nrRevizii;
            }
            void setNrRevizii(int nrReviziiNou)
            {
                if(nrReviziiNou>0)
                {
                    this->nrRevizii=nrReviziiNou;
                }
                else
                {
                    throw "Numarul de revizii nu poate fi negativ!";
                }
            }
            float* getIstoricConsum()
            {
                if(this->nrRevizii ==0 || this->istoricConsum == nullptr)
                    return nullptr;
                float* istoricNou=new float[this->nrRevizii];
                for(int i=0; i<this->nrRevizii; i++)
                    istoricNou[i]=this->istoricConsum[i];
                return istoricNou;
            }
            void setIstoricConsum(float* vector, int nrR)
            {
                setNrRevizii(nrR);
                if(this->istoricConsum!=nullptr)
                {
                    delete[] this->istoricConsum;
                }
                if(this->nrRevizii >0 && vector!=nullptr)
                {
                    this->istoricConsum=new float[this->nrRevizii];
                    for(int i=0; i<this->nrRevizii; i++)
                        this->istoricConsum[i]=vector[i];
                }
                else
                    this->istoricConsum=nullptr;
                delete[] vector;
            }
            ~Masina()
            {
                if(this->istoricConsum!=nullptr)
                    delete[] this->istoricConsum;
            }
};
int Masina::nrMasini=0;
int main()
{
    Masina m3(1,"Opel",2,new float[2]{5.6,4.7});
    Masina m4;
    m4=m3;
    m4.afisareMasina();
    Masina mDacia;
    mDacia.afisareMasina();
    try{
        mDacia.setNrRevizii(-1);
    }
    catch(const char* mesaj)
    {
        cout<<endl<<"Eroare: "<<mesaj;
    }
    float* consum=new float[2] {7.5,8.2};
    Masina m1(1,"Dacia",2,consum);
    Masina m2= m1;
    m2.afisareMasina();
    cout<<endl<<"Noul numar de revizii este: "<<mDacia.getNrRevizii();
    mDacia.setIstoricConsum(new float[3] {7.6,6.8,7.2},3);
    float* vectorConsum=mDacia.getIstoricConsum();
    cout<<endl<<"Consumul preluat este: ";
    if(vectorConsum!=nullptr)
    {
        for(int i=0; i<mDacia.getNrRevizii(); i++)
            cout<<vectorConsum[i]<<" l/100kmh, ";
        delete[]  vectorConsum;
    }
    mDacia.afisareMasina();
    float* consumInitial=new float[2] {8.1,8.9};
    Masina* pBmw=new Masina(10,"BMW",2,consumInitial);
    pBmw->afisareMasina();
    delete pBmw;
    cout<<endl<<"Am construit in total "<<Masina::nrMasini<<" masini!";
}
