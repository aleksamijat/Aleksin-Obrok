#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

enum TipMeso{SVINJETINA, JUNETINA, PILETINA, BEZ_MESA};

class Meso{
private:
    int gramaza;
    TipMeso tipM;
public:
    Meso(){
        gramaza = 0;
        tipM = BEZ_MESA;
    }
    Meso(const Meso& meso){
        gramaza = meso.gramaza;
        tipM = meso.tipM;
    }
    bool SetGramaza(int gram)
    {
        if(gram > 0 && gram < 1000)
        {
            gramaza = gram;
            return true;
        }
        return false;
    }
    int GetGramaza()const
    {
        return gramaza;
    }
    void SetVrstaMesa(TipMeso vrstaM)
    {
        tipM = vrstaM;
    }
    TipMeso GetVrstaMesa()const
    {
        return tipM;
    }
};

void IspisiMeso(const Meso& meso)
{
    string tipM;
    switch(meso.GetVrstaMesa())
    {
    case SVINJETINA:
        cout << "Svinjetina" << endl;
        break;
    case JUNETINA:
        cout << "Junetina" << endl;
        break;
    case PILETINA:
        cout << "Piletina" << endl;
        break;
    case BEZ_MESA:
        cout << "Bez mesa" << endl;
        return;
    }
}

enum VrstaPriloga{RIZA, POMFRIT, PASULJ, TESTENINA, BEZ_PRILOGA};

class Prilog
{
private:
    VrstaPriloga vrstaPriloga;
public:
    Prilog(){
        vrstaPriloga = BEZ_PRILOGA;
    }
    Prilog(const Prilog& prilog){
        vrstaPriloga = prilog.vrstaPriloga;
    }
    void SetPrilog(VrstaPriloga vrstaP){
        vrstaPriloga = vrstaP;
    }
    VrstaPriloga GetPrilog()const{
        return vrstaPriloga;
    }
};

void IspisiPrilog(const Prilog& prilog)
{
    switch(prilog.GetPrilog())
    {
    case POMFRIT:
        cout << "Pomfrit" << endl;
        break;
    case RIZA:
        cout << "Riza" << endl;
        break;
    case PASULJ:
        cout << "Pasulj" << endl;
        break;
    case TESTENINA:
        cout << "Testenina" << endl;
        break;
    case BEZ_PRILOGA:
        cout << "Bez priloga" << endl;
        break;
    }
}

enum StanjeObroka{POCETAK_ODABIRA, ODABRANO_MESO, ODABRAN_PRILOG, SPREMAN, ZAGOREO};

class Obrok
{
private:
    Meso meso;
    Prilog prilog;
    StanjeObroka stanje;
public:
    Obrok() : meso(), prilog(){
        stanje = POCETAK_ODABIRA;
    }

    Obrok(TipMeso tipM, int gramaza, VrstaPriloga vrstaPriloga){
        if(!meso.SetGramaza(gramaza)){
            meso.SetVrstaMesa(tipM);
            prilog.SetPrilog(vrstaPriloga);
            stanje = ODABRAN_PRILOG;
        }
        stanje = POCETAK_ODABIRA;
    }

    Meso GetMeso()const{
        return meso;
    }

    Prilog GetPrilog()const{
        return prilog;
    }

    StanjeObroka GetStanjeObroka()const{
        return stanje;
    }

    bool OdaberiMeso(TipMeso tipM, int gramaza){
        if(stanje == POCETAK_ODABIRA)
        {
            if(meso.SetGramaza(gramaza)){
                meso.SetVrstaMesa(tipM);
                stanje = ODABRANO_MESO;
                return true;
            }
        }
        return false;
    }

    bool OdaberiPrilog(VrstaPriloga vrstaPriloga){
        if(stanje == ODABRANO_MESO){
            prilog.SetPrilog(vrstaPriloga);
            stanje = ODABRAN_PRILOG;
            return true;
        }
        return false;
    }
    void Spremi(){
        if(stanje == ODABRAN_PRILOG){
            stanje = (rand() % 10 <= 8) ? SPREMAN : ZAGOREO;
        }
    }
};

void IspisiObrok(const Obrok& obrok){
    switch(obrok.GetStanjeObroka()){
        case POCETAK_ODABIRA:
            cout << "POCETAK_ODABIRA" << endl;
            break;
        case ODABRANO_MESO:
            cout << "ODABRANO_MESO" << endl;
            break;
        case ODABRAN_PRILOG:
            cout << "ODABRAN_PRILOG" << endl;
            break;
        case SPREMAN:
            cout << "SPREMAN" << endl;
            break;
        case ZAGOREO:
            cout << "ZAGOREO" << endl;
            break;
    }
    IspisiMeso(obrok.GetMeso());
    IspisiPrilog(obrok.GetPrilog());
}

bool Meni(Obrok& obrok)
{
    cout << "1) Odaberi meso" << endl << "2) Odaberi prilog" << endl << "3) Spremi" << endl << "4) Prikazi obrok" << endl << "5) Exit" << endl;
    int izbor;
    do{
        cin >> izbor;
    }while(izbor < 1 || izbor > 5);
    switch(izbor){
        case 1:
            if(obrok.GetStanjeObroka() == POCETAK_ODABIRA){
                cout << "1) Svinjetina" << endl << "2) Junetina" << endl << "3) Piletina" << endl << "4) Bez mesa";
                do{
                    cin >> izbor;
                }while(izbor < 1 || izbor > 4);
                int kolicina;
                cout << "Unesi gramazu:" << endl;
                cin >> kolicina;
                if(obrok.OdaberiMeso((TipMeso)izbor, kolicina)){
                    cout << "Uspesan odabir" << endl;
                }
                else{
                    cout << "Neupesan odabir" << endl;

                }
            }
            else{
                cout << endl << "Vec ste izabrali" << endl;
            }
            break;
        case 2:
            if(obrok.GetStanjeObroka() == ODABRANO_MESO){
                cout << "1) Riza" << endl << "2) Pomfrit" << endl << "3) Pasulj" << endl << "4) Testenina" << endl << "5) Bez priloga" << endl;
            do{
                cin >> izbor;
            }while(izbor < 1 || izbor > 5);
            obrok.OdaberiPrilog((VrstaPriloga)izbor);
            cout << "Uspesan odabir" << endl;

            }
            else
            {
                if(obrok.GetStanjeObroka() == POCETAK_ODABIRA){
                    cout << endl << "Meso nije odabrano";
                }
                else{
                cout << endl << "Vec ste izabrali" << endl;
                }
            }
            break;
        case 3:
            if(obrok.GetStanjeObroka() == ODABRAN_PRILOG){
                obrok.Spremi();
                cout << endl << "Uspesan odabir" << endl;
            }
            else{
                cout << endl << "Niste sve izabrali" << endl;
            }
            break;
        case 4:
            IspisiObrok(obrok);
            break;
        case 5:
            return true;
        }
    return false;
}

int main()
{
    srand(time(NULL));
    Obrok obrok;
    while(!Meni(obrok));
    return 0;
}
