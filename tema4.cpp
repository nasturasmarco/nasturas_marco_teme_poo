#include<iostream>
#include<string>
using namespace std;
enum TipRestaurant { TRADITIONAL = 1, FAST_FOOD = 2 };
class Restaurant {
private:
	const int id;
	float pretMediu;
	string denumire;
	TipRestaurant tip;
	int nrMese;
	float* vectorNote;
public:
	static int nrRestaurante;
	Restaurant() : id(++nrRestaurante) {
		this->denumire = "Default";
		this->nrMese = 0;
		this->pretMediu = 0;
		this->tip = TRADITIONAL;
		this->vectorNote = nullptr;
	}
	Restaurant(int id, float pretMediu, string denumire, TipRestaurant tip, int nrMese, float* vectorNote) : id(id) {
		this->denumire = denumire;
		this->pretMediu = pretMediu;
		this->tip = tip;
		this->nrMese = nrMese;
		if (nrMese > 0 && vectorNote != nullptr) {
			this->vectorNote = new float[this->nrMese];
			for (int i = 0; i < this->nrMese; i++) {
				this->vectorNote[i] = vectorNote[i];
			}
		}
		else {
			this->vectorNote = nullptr;
			this->nrMese = 0;
		}
		nrRestaurante++;
	}
	Restaurant(const Restaurant& r) : id(++nrRestaurante) {
		this->denumire = r.denumire;
		this->nrMese = r.nrMese;
		this->pretMediu = r.pretMediu;
		this->tip = r.tip;
		if (r.vectorNote != nullptr) {
			this->vectorNote = new float[this->nrMese];
			for (int i = 0; i < this->nrMese; i++) {
				this->vectorNote[i] = r.vectorNote[i];
			}
		}
		else {
			this->vectorNote = nullptr;
		}
	}
	Restaurant& operator=(const Restaurant& r) {
		if (this == &r) return *this;
		this->denumire = r.denumire;
		this->pretMediu = r.pretMediu;
		this->nrMese = r.nrMese;
		this->tip = r.tip;
		if (this->vectorNote != nullptr) {
			delete[] this->vectorNote;
			this->vectorNote = nullptr;
		}
		if (r.vectorNote != nullptr) {
			this->vectorNote = new float[this->nrMese];
			for (int i = 0; i < this->nrMese; i++) {
				this->vectorNote[i] = r.vectorNote[i];
			}
		}
		else {
			this->vectorNote = nullptr;
		}
		return *this;
	}
	void afisareRestaurant() {
		cout << endl << "Id: " << this->id;
		cout << endl << "Denumire: " << this->denumire;
		cout << endl << "Pret mediu: " << this->pretMediu << " lei";
		cout << endl << "Nr mese: " << this->nrMese;
		cout << endl << "Tip: ";
		if (this->tip == TRADITIONAL) cout << "TRADITIONAL";
		else cout << "FAST_FOOD";
		if (this->nrMese > 0 && this->vectorNote != nullptr) {
			cout << endl << "Note mese: ";
			for (int i = 0; i < this->nrMese - 1; i++) {
				cout << this->vectorNote[i] << ", ";
			}
			cout << this->vectorNote[this->nrMese - 1] << ".";
		}
	}
	int getNrMese() { return this->nrMese; }
	void setNrMese(int nrMeseNou) {
		if (nrMeseNou >= 0) this->nrMese = nrMeseNou;
		else throw "Valoare negativa pentru numarul de mese";
	}
	float* getVectorNote() {
		if (this->nrMese == 0 || this->vectorNote == nullptr) return nullptr;
		float* vectorNoteNou = new float[this->nrMese];
		for (int i = 0; i < this->nrMese; i++) {
			vectorNoteNou[i] = this->vectorNote[i];
		}
		return vectorNoteNou;
	}
	void setVectorNote(float* vector, int nrM) {
		setNrMese(nrM);
		if (this->vectorNote != nullptr) delete[] this->vectorNote;
		this->vectorNote = new float[this->nrMese];
		for (int i = 0; i < this->nrMese; i++) {
			this->vectorNote[i] = vector[i];
		}
		delete[] vector;
	}
	~Restaurant() {
		if (this->vectorNote != nullptr) delete[] this->vectorNote;
	}
	bool operator<(const Restaurant& r) { return this->nrMese < r.nrMese; }
	void operator+=(float pretDeAdunat) { this->pretMediu += pretDeAdunat; }
	bool operator!() { return this->pretMediu > 0; }
	float operator()(float valoareDeAdaugat) { return this->pretMediu + valoareDeAdaugat; }
	float& operator[](int index) {
		if (index >= 0 && index < this->nrMese) return this->vectorNote[index];
		else throw exception();
	}
	friend ostream& operator<<(ostream& out, const Restaurant& r) {
		out << endl << "--- Operator de afisare (friend) ---";
		out << endl << "Id: " << r.id;
		out << endl << "Denumire: " << r.denumire;
		out << endl << "Pret mediu: " << r.pretMediu;
		out << endl << "Tip: ";
		if (r.tip == TRADITIONAL) out << "TRADITIONAL";
		else if (r.tip == FAST_FOOD) out << "FAST_FOOD";
		out << endl << "Nr mese: " << r.nrMese;
		if (r.vectorNote != nullptr && r.nrMese > 0) {
			out << endl << "Vector note: ";
			for (int i = 0; i < r.nrMese - 1; i++) {
				out << r.vectorNote[i] << " stele, ";
			}
			out << r.vectorNote[r.nrMese - 1] << " stele.";
		}
		return out;
	}
	friend istream& operator>>(istream& in, Restaurant& r);
	Restaurant operator++(int) {
		Restaurant copie = *this;
		this->pretMediu++;
		return copie;
	}
	Restaurant& operator++() {
		this->pretMediu++;
		return *this;
	}
	explicit operator int() { return this->nrMese; }
};
int Restaurant::nrRestaurante = 0;
istream& operator>>(istream& in, Restaurant& r) {
	cout << endl << "Pret mediu: ";
	in >> r.pretMediu;
	cout << "Denumire: ";
	in >> r.denumire;
	cout << "Tip (1 - TRADITIONAL, 2 - FAST_FOOD): ";
	int optiune;
	in >> optiune;
	if (optiune == 1) r.tip = TRADITIONAL;
	else r.tip = FAST_FOOD;
	cout << "Nr mese: ";
	in >> r.nrMese;
	if (r.vectorNote != nullptr) {
		delete[] r.vectorNote;
		r.vectorNote = nullptr;
	}
	if (r.nrMese > 0) {
		r.vectorNote = new float[r.nrMese];
		for (int i = 0; i < r.nrMese; i++) {
			cout << "vectorNote[" << i << "]: ";
			in >> r.vectorNote[i];
		}
	}
	return in;
}
int main() {
	Restaurant rTraditional;
	rTraditional += 50.5f;
	if (!rTraditional) cout << endl << "Pret mediu nenul!";
	else cout << endl << "Pret mediu nul!";
	cout << endl << "Apel operator functie: " << rTraditional(15.0f);
	cout << rTraditional;
	Restaurant r1 = rTraditional++;
	cout << endl << "Dupa postincrementare (r1):" << r1;
	Restaurant r2 = ++rTraditional;
	cout << endl << "Dupa preincrementare (r2):" << r2;
	float* note = new float[3] { 4.5f, 5.0f, 4.0f };
	Restaurant* pModern = new Restaurant(10, 120.0f, "Urban Bistro", TRADITIONAL, 3, note);
	pModern->afisareRestaurant();
	if (rTraditional < *pModern) cout << endl << "Restaurantul Traditional are mai putine mese decat cel Modern!";
	else cout << endl << "Restaurantul Modern are mai putine mese!";
	(*pModern)[0] = 4.8f;
	cout << endl << "Apel operator index (noua valoare nota 0): " << (*pModern)[0];
	cout << endl << "Am construit in total " << Restaurant::nrRestaurante << " restaurante!";
	cout << endl << "Cast explicit la int (nr mese): " << (int)(*pModern) << endl;
	delete pModern;
	return 0;
}
