#include<iostream>
#include<string>
using namespace std;
enum TipRestaurant { TRADITIONAL = 1, FAST_FOOD = 2 };
class ExceptieCustom : public exception {
public:
	ExceptieCustom(const char* mesaj) : exception(mesaj) {}
};
class Restaurant {
protected:
	const int id;
	float pretMediu;
	string denumire;
	TipRestaurant tip;
	int nrMese;
	float* vectorNote;
public:
	static int nrRestaurante;
	static const float PRET_MEDIU_MINIM;
	Restaurant() : id(++nrRestaurante) {
		this->denumire = "Default";
		this->nrMese = 0;
		this->pretMediu = PRET_MEDIU_MINIM;
		this->tip = TRADITIONAL;
		this->vectorNote = nullptr;
	}
	Restaurant(int id, float pretMediu, string denumire, TipRestaurant tip, int nrMese, float* vectorNote) : id(id) {
		if (pretMediu < PRET_MEDIU_MINIM) {
			throw ExceptieCustom("Pret mediu prea mic!");
		}
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
		if (r.vectorNote != nullptr && r.nrMese > 0) {
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
		if (r.vectorNote != nullptr && r.nrMese > 0) {
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
	virtual void afisareRestaurant() {
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
		else throw ExceptieCustom("Valoare negativa pentru numarul de mese!");
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
	virtual ~Restaurant() {
		if (this->vectorNote != nullptr) delete[] this->vectorNote;
	}
	virtual float getProcentReducere() = 0;
	bool operator<(const Restaurant& r) { return this->nrMese < r.nrMese; }
	void operator+=(float pretDeAdunat) { this->pretMediu += pretDeAdunat; }
	bool operator!() { return this->pretMediu > 0; }
	float operator()(float valoareDeAdaugat) { return this->pretMediu + valoareDeAdaugat; }
	float& operator[](int index) {
		if (index >= 0 && index < this->nrMese) return this->vectorNote[index];
		else throw ExceptieCustom("Index invalid!");
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
	Restaurant& operator++() {
		this->pretMediu++;
		return *this;
	}
	explicit operator int() { return this->nrMese; }
};
int Restaurant::nrRestaurante = 0;
const float Restaurant::PRET_MEDIU_MINIM = 10;
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
class RestaurantCuReducere : public Restaurant {
private:
	float procentReducere;
public:
	RestaurantCuReducere() : Restaurant() {
		this->procentReducere = 0;
	}
	RestaurantCuReducere(int id, float pretMediu, string denumire, TipRestaurant tip, int nrMese, float* vectorNote, float procentReducere)
		: Restaurant(id, pretMediu, denumire, tip, nrMese, vectorNote) {
		this->procentReducere = procentReducere;
	}
	void afisareRestaurant() override {
		this->Restaurant::afisareRestaurant();
		cout << endl << "Procent reducere: " << this->procentReducere << "%";
	}
	float getProcentReducere() override {
		return this->procentReducere;
	}
};
class OperatieNota {
public:
	virtual float adunareBacsis(float nota, float bacsis) = 0;
	virtual float scadereReducere(float nota, float reducere) = 0;
};
class CalculatorNota : public OperatieNota {
public:
	CalculatorNota() {}
	float adunareBacsis(float nota, float bacsis) override {
		return nota + bacsis;
	}
	float scadereReducere(float nota, float reducere) override {
		return nota - reducere;
	}
};
int main() {
	try {
		RestaurantCuReducere rInvalid(1, 5.0f, "Cantina", FAST_FOOD, 0, nullptr, 10);
	}
	catch (exception& e) {
		cout << endl << "Exceptie prinsa: " << e.what();
	}
	float note1[2] = { 4.5f, 5.0f };
	float note2[3] = { 4.0f, 4.2f, 4.8f };
	Restaurant* vectorRestaurante[3];
	vectorRestaurante[0] = new RestaurantCuReducere(1, 80.0f, "La Mama", TRADITIONAL, 2, note1, 10);
	vectorRestaurante[1] = new RestaurantCuReducere(2, 45.0f, "Burger House", FAST_FOOD, 3, note2, 15);
	vectorRestaurante[2] = new RestaurantCuReducere(3, 120.0f, "Urban Bistro", TRADITIONAL, 2, note1, 20);
	for (int i = 0; i < 3; i++) {
		vectorRestaurante[i]->afisareRestaurant();
		cout << endl << "Reducere aplicata: " << vectorRestaurante[i]->getProcentReducere() << "%";
		cout << endl << "---------------------------";
		delete vectorRestaurante[i];
	}
	Restaurant* pRestaurant = new RestaurantCuReducere();
	pRestaurant->afisareRestaurant();
	delete pRestaurant;
	OperatieNota* calcul = new CalculatorNota();
	cout << endl << "\nTotal cu bacsis: " << calcul->adunareBacsis(150.0f, 15.0f) << " lei";
	cout << endl << "Total cu reducere: " << calcul->scadereReducere(150.0f, 20.0f) << " lei" << endl;
	delete calcul;
	return 0;
}
