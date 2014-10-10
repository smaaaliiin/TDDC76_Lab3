/*
 * FILNAMN:       lab2.cc
 * LABORATION:    Lab 2
 * PROGRAMMERARE: Bj�rn Wilke, 870617-0415, Ii#a
 *                Malin Aspelin, 910527-5524, FyN3
 * DATUM:         2014-10-05
 *
 * BESKRIVNING 
 * Ett testprogram d�r anv�ndaren kan skapa moneyobjekt.
 * Anv�ndaren kan �ven testa ett antal operationer och
 * tilldelningsmetoder med hj�lp av de skapade moneyobjekten.
 * 
 */
#include <iostream>
#include <string>
#include <vector>
#include "Monetary.h"

using namespace std;
using namespace monetary;

void new_money(vector<Money>&);
void new_money_copy(vector<Money>&);
void list_money(const vector<Money>&);
void print_money(const vector<Money>&);
void change_money(vector<Money>&);
void add_money(vector<Money>&);
void sub_money(vector<Money>&);
void up_prefix(vector<Money>&);
void up_postfix(vector<Money>&);
void down_prefix(vector<Money>&);
void down_postfix(vector<Money>&);
void compare_money(vector<Money>&);
int choose(const vector<Money>&) noexcept;

int main()

{
  vector<Money> list;
  int choice{13};
  
  while (choice != 0) //Main menu
    {
      choice = 13;
      cout << "\n\n\n-------------------------------\n"
	   << "You have currently '" << list.size() 
	   << "' Money objects saved.\n\n"
	   << "Menu choices:\n"
	   << "1. Skapa ett nytt Money objekt\n"
	   << "2. Skapa ett nytt Money objekt genom kopiering\n"
	   << "3. Lista alla nuvarande Money objekt\n"
	   << "4. Skriv ut ett objekt\n"
	   << "5. �ndra v�rdet p� ett objekt med hj�lp av tilldelning\n"
	   << "6. Addera tv� objekt och spara summan i en av dem\n"
	   << "7. Subtrahera tv� objekt och spara summan i en av dem\n"
	   << "8. Stega upp ett objekt, prefix\n"
	   << "9. Stega upp ett objekt, postfix\n"
	   << "10. Stega ner ett objekt, prefix\n"
	   << "11. Stega ner ett objekt, postfix\n"
	   << "12. J�mf�r tv� objekt (p� alla t�nkbara s�tt!)\n"
	   << "0. Avsluta programmet\n";
      
      while ( !(choice >= 0 && choice < 13) )
	{
	  cin >> choice;
	  
	  cout << "DU VALDE: " << choice << "\n\n\n";
	  
	  if (choice == 1) // Skapa ett nytt Money objekt
	    {
	      new_money(list);
	    }
	  else if (list.size() > 0 && choice == 2) // Skapa ett nytt Money objekt genom kopiering
	    {
	      new_money_copy(list);
	    }
	  else if (choice == 3) // Lista alla nuvarande Money objekt
	    {
	      cout << "Du har f�ljande objekt sparade: \n";
	      list_money(list);
	    }
	  else if (list.size() > 0 && choice == 4) // Skriv ut ett objekt
	    {
	      print_money(list);
	    }
	  else if (list.size() > 0 && choice == 5) // �ndra v�rdet p� ett objekt
	    {
	      change_money(list);
	    }
	  else if (list.size() > 0 && choice == 6) // Addera tv� objekt och spara summan i en av dem
	    {
	      add_money(list);
	    }
	  else if (list.size() > 0 && choice == 7) // Subtrahera tv� objekt och spara summan i en av dem
	    {
	      sub_money(list);
	    }
	  else if (list.size() > 0 && choice == 8) // Stega upp ett objekt, prefix
	    {
	      up_prefix(list);
	    }
	  else if (list.size() > 0 && choice == 9) // Stega upp ett objekt, postfix
	    {
	      up_postfix(list);
	    }
	  else if (list.size() > 0 && choice == 10) // Stega nerett objekt, prefix
	    {
	      down_prefix(list);
	    }
	  else if (list.size() > 0 && choice == 11) // Stega ner ett objekt, postfix
	    {
	      down_postfix(list);
	    }
	  else if (list.size() > 0 && choice == 12) // J�mf�r tv� objekt (p� alla t�nkbara s�tt!)
	    {
	      compare_money(list);
	    }
	  else if (choice == 0)
	    {
	    }
	  else
	    {
	      cout << "M�ste ange ett korrekt menyval.\n";
	    }
	  cin.ignore();
	}
      
    } // Main menu
  cout << "Tack och hejd�!\n\n"; // Denna text skrev i Malaga. 23 grader och Mojitos frack yeah!\n\n";
  
  return 0;
    
}


/*
 * FUNKTION new_money(vector<Money>& list)
 *
 * Skapar nya moneyobjekt d� anv�ndaren matar in en valuta.
 */

void new_money(vector<Money>& list)
{
  cout << "Skriv in en ny valuta. Skrivs p� formatet \"BBB UU.CC\" eller med ospecifiserad valuta.\n";
  Money nm;
  try
    {
      cin >> nm;
    }
  catch (const monetary_error& e)
    {
      cout << "N�got gick fel! B�ttre lycka n�sta g�ng.\n"
	   << "ERROR : " << e.what() << '\n';
    }
  list.push_back(nm);
}


/*
 * FUNKTION new_money_copy(vector<Money>& list)
 *
 * Skapar nya moneyobjekt genom att kopiera en redan deifnierad valuta.
 */
void new_money_copy(vector<Money>& list)
{
  if (list.size() != 0)
    {
      cout << "Du har f�ljande objekt sparade. Vilket vill du skapa en ny kopia av?\n";
      list_money(list);
      Money nm{ list[ choose(list) ] };
      list.push_back(nm);
    }
  else
    {
      cout << "Det finns inget objekt att skapa en kopia av\n";
    }
}


/*
 * FUNKTION list_money(const vector<Money>& list)
 *
 * Skriver ut alla skapade moneyobjekt.
 */
void list_money(const vector<Money>& list)
{
  for (unsigned i = 0; i < list.size(); ++i)
    {
      cout << (i+1) << ".  " << list[i] << "\n";
    }
}


/*
 * FUNKTION print_money(const vector<Money>& list)
 *
 * Skriver endast ut ett valt moneyobjekt.
 */
void print_money(const vector<Money>& list)
{
  cout << "Vilket objekt vill du skriva ut? Du har '"
       << list.size() << "' objekt.\n";
  try
    {
      cout << list[choose(list)] << '\n';
    }
  catch (const monetary_error& e)
    {
      cout << "N�got gick fel! B�ttre lycka n�sta g�ng.\n"
	   << "ERROR : " << e.what() << '\n';
    }
}


/*
 * FUNKTION change_money(vector<Money>& list)
 *
 * �ndrar p� ett redan existerande moneyobjekt med
 * hj�lp av tilldelning.
 */
void change_money(vector<Money>& list)
{
  Money list_new{};
  cout << "Vilket objekt vill du �ndra p�? Du har '"
       << list.size() << "' objekt.\n";
  try
    {
      int i{choose(list)};
      cout << "Vad vill du �ndra det till? VVV UU.CC\n";
      //cin >> list[ i ];
      cin >> list_new;      
      list[i] = list_new;
    }
  catch (const monetary_error& e)
    {
      cout << "N�got gick fel! B�ttre lycka n�sta g�ng.\n"
	   << "ERROR : " << e.what() << '\n';
    }
  
}


/*
 * FUNKTION add_money(vector<Money>& list)
 *
 * Adderar tv� moneyobjekt och sparar resultatet i det f�rsta
 * moneyobjektet.
 */
void add_money(vector<Money>& list)
{
  cout << "V�lj 2 objekt som ska adderas med varandra, det f�rsta tar v�rdet av summan (+=).\n";
  list_money(list);
  
  int a{choose(list)};
  int b{choose(list)};
  try
    {
      list[a] += list[b];  
    }
  catch (const monetary_error& e)
    {
      cout << "ERROR: " << e.what() << "\n";
    }
}


/*
 * FUNKTION sub_money(vector<Money>& list) 
 *
 * Adderar tv� moneyobjekt och sparar resultatet i det f�rsta
 * moneyobjektet.
 */
void sub_money(vector<Money>& list)
{
  cout << "V�lj 2 objekt som ska subtraheras med varandra, det f�rsta tar v�rdet av summan (+=).\n";
  list_money(list);
  
  int a{choose(list)};
  int b{choose(list)};

  try
    {  
      list[a] -= list[b]; 
    }
  catch (const monetary_error& e)
    {
      cout << "ERROR: " << e.what() << "\n";
    }

}


/*
 * FUNKTION up_prefix(vector<Money>& list)
 *
 * R�knar upp moneyobjektet prefixt.
 */
void up_prefix(vector<Money>& list)
{
  list_money(list);
  cout << "V�lj ett objekt som ska stegas: ";
  int i{choose(list)};
  cout << "Objektets v�rde, stegning p� f�rsta raden:\n"
       << ++list[i] << '\n'
       << list[i] << '\n';
}


/*
 * FUNKTION up_postfix(vector<Money>& list)
 *
 * R�knar upp moneyobjektet postfixt.
 */
void up_postfix(vector<Money>& list)
{
  list_money(list);
  cout << "V�lj ett objekt som ska stegas: ";
  int i{choose(list)};
  cout << "Objektets v�rde, stegning p� f�rsta raden:\n"
       << list[i]++ << '\n'
       << list[i] << '\n';
}


/*
 * FUNKTION down_prefix(vector<Money>& list)
 *
 * R�knar ner moneyobjektet prefixt.
 */
void down_prefix(vector<Money>& list)
{
  list_money(list);
  cout << "V�lj ett objekt som ska stegas: ";
  int i{choose(list)};
  cout << "Objektets v�rde, stegning p� f�rsta raden:\n"
       << --list[i] << '\n'
       << list[i] << '\n';
}


/*
 * FUNKTION down_postfix(vector<Money>& list)
 *
 * R�knar ner moneyobjektet postfixt.
 */
void down_postfix(vector<Money>& list)
{
  list_money(list);
  cout << "V�lj ett objekt som ska stegas: ";
  int i{choose(list)};
  cout << "Objektets v�rde, stegning p� f�rsta raden:\n"
       << list[i]-- << '\n'
       << list[i] << '\n';
}


/*
 * FUNKTION down_postfix(vector<Money>& list)
 *
 * J�mf�r tv� moneyobjekt med ett antal opperatorer.
 */
void compare_money(vector<Money>& list)
{
  list_money(list);
  cout << "V�lj tv� objekt som ska j�mf�ras med varandra: ";
  int a{choose(list)};
  int b{choose(list)};
    
  cout << "a : " << list[a] << "\n"
       << "b : " << list[b] << "\n";

  try
    {
      cout << list[a] << "<" << list[b];
      if ( list[a] < list[b] )
	{
	  cout << " g�ller!\n";
	}
      else
	{
	  cout << " g�ller inte!\n";
	}
      
      cout << list[a] << ">" << list[b];
      if ( list[a] > list[b] )
	{
	  cout << " g�ller!\n";
	}
      else
	{
	  cout << " g�ller inte!\n";
	}

      cout << list[a] << "<=" << list[b];
      if ( list[a] <= list[b] )
	{
	  cout << " g�ller!\n";
	}
      else
	{
	  cout << " g�ller inte!\n";
	}

      cout << list[a] << ">=" << list[b];
      if ( list[a] >= list[b] )
	{
	  cout << " g�ller!\n";
	}
      else
	{
	  cout << " g�ller inte!\n";
	}

      cout << list[a] << "==" << list[b];
      if ( list[a] == list[b] )
	{
	  cout << " g�ller!\n";
	}
      else
	{
	  cout << " g�ller inte!\n";
	}

      cout << list[a] << "!=" << list[b];
      if ( list[a] != list[b] )
	{
	  cout << " g�ller!\n";
	}
      else
	{
	  cout << " g�ller inte!\n";
	}

    } // try
  catch (const monetary_error& e)
    {
      cout << "N�got gick fel! B�ttre lycka n�sta g�ng.\n"
	   << "ERROR : " << e.what() << '\n';
    } // catch
}


int choose(const vector<Money>& list) noexcept
{
  unsigned choice{0};
  while ( choice < 1 || choice > list.size() )
    { 
      cin >> choice;
      if (choice < 1 || choice > list.size() )
	{
	  cout << "Felaktigt val!\n";
	}
    }
  return (choice-1);
}
