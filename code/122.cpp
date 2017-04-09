#define _USE_MATH_DEFINES 

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

const double M_PI = acos(-1); 

class Figuur {
	public:
		virtual double omtrek() const = 0;
		virtual double oppervlakte() const = 0;
		virtual void schrijf_soort(ostream & out) const = 0;
		friend ostream& operator<<(ostream& out, const Figuur & f) {
			f.schrijf_soort(out);
			out<<" met omtrek "<<f.omtrek()<<" en oppervlakte "<<f.oppervlakte();		
			return out;	
		}		
};

class Cirkel : public Figuur {
	private:
		double straal;
		void schrijf_soort(ostream & out) const {
			out<<"cirkel";
		}
	public:
		Cirkel(double s):straal(s){}
		double omtrek() const {
			return 2*M_PI*straal;
		}
		double oppervlakte() const {
			return M_PI*straal*straal;	
		}
};

class Rechthoek : public Figuur {
	private:
		double lengte, breedte;	
		void schrijf_soort(ostream & out) const {
			out<<"rechthoek";
		}
	public:
		Rechthoek(double l, double b) : lengte(l), breedte(b){}
		double omtrek() const {
			return 2*(lengte+breedte);
		}
		double oppervlakte() const {
			return lengte*breedte;	
		}
};

class Vierkant : public Rechthoek {
	private:		
		void schrijf_soort(ostream & out) const {
			out<<"vierkant";
		}
	public:
		Vierkant(double z) : Rechthoek(z,z) {}
};

void lees(vector<Figuur*> & figuren, string bestandsnaam) {
    ifstream input(bestandsnaam);
    string soort;
    input >> soort;
    while (!input.fail() ){
       if (soort == "rechthoek"){
           double lengte, breedte;
           input >> lengte >> breedte;
           figuren.push_back(new Rechthoek(lengte,breedte));     
       }
       else if(soort == "vierkant") {
           double zijde;
           input >> zijde;
           figuren.push_back(new Vierkant(zijde));         
       }   
       else if(soort == "cirkel"){
           double straal;
           input >> straal;     
           figuren.push_back(new Cirkel(straal));
       }
       else{
            string c;
            getline(input,c);  // om overschot in te lezen
       }
       input >> soort;      
    }    
    input.close();
}
    
int main() {
	
	vector<Figuur*> figuren;
	lees(figuren,"figuren.txt");
	
	for(int i=0; i<figuren.size(); i++){
		cout << *figuren[i] << endl;
	}
		
	for(int i=0; i<figuren.size(); i++){
		delete figuren[i];	
	}	
			
	return 0;	
}