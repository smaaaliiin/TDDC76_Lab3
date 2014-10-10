/*
 * FILNAMN:       Monetary.cc
 * LABORATION:    Lab 2
 * PROGRAMMERARE: Björn Wilke, 870617-0415, Ii#a
 *                Malin Aspelin, 910527-5524, FyN3
 * DATUM:         2014-10-10
 *
 * BESKRIVNING 
 * Filen innehåller deklarationerdefinitioner av alla funktioner som är
 * skrivna för att hantera klassen Money.
 * 
 */

#include "Monetary.h"

using namespace std;

namespace monetary
{

  /********** KONSTRUKTORER OCH DESTRUKTOR **********/
  
  /*
   * FUNKTION Money(const int unit, const int centi)
   *
   * Konstruktor av Money. Kräver inga argument.
   */
  Money::Money(const int unit, const int centi) 
    : unit_(unit),
      centi_(centi)
  {
    if (unit_ < 0 || centi_ < 0 || centi_ > 99)
      {
	unit_ = 0;
	centi_ = 0;
	throw monetary_error{"inga negativa värden"};
      }
  }


  /*
   * FUNKTION Money(const std::string& cur, const int unit, const int centi)
   *
   * Konstruktor av Money. Kräver minst en sträng som argument.
   */
  Money::Money(const std::string& cur, const int unit, const int centi)
    : currency_(cur),
      unit_(unit),
      centi_(centi)
  {
    if (unit_ < 0 || centi_ < 0 || centi_ > 99)
      {
	currency_ = "";
	unit_ = 0;
	centi_ = 0;
	throw monetary_error{"inga negativa värden"};
      }  
  }


  /*
   * FUNKTION Money(const Money& other)
   *
   * Kopieringskonstruktor för Money.
   */
  Money::Money(const Money& other)
    : currency_(other.currency_),
      unit_(other.unit_),
      centi_(other.centi_)
  {
  }


  /*
   * FUNKTION ~Money()
   *
   * Destruktor för Money.
   */
  Money::~Money()
  {
  }


  /********** FUNKTIONER **********/
 
  /*
   * FUNKTION print(std::ostream& stream)
   *
   * Skriver ut objektet till utströmmen stream genom användning av
   * operatorn <<.
   */
  void Money::print(std::ostream& stream) const
  {
    if ( currency_.empty() )
      {
	if (centi_ < 10)
	  {
	    stream << unit_ << ".0" << centi_;
	  }
	else
	  {
	    stream << unit_ << "." << centi_;
	  }
      }
    else
      {
	if (centi_ < 10)
	  {
	    stream << currency_ << " " 
		   << unit_ << ".0" 
		   << centi_ ;
	  }
	else
	  {
	    stream << currency_ << " " 
		   << unit_ << "." 
		   << centi_ ;
	  }      
      }
  }


  /*
   * FUNKTION currency() const
   *
   * Retunerar värdet för currency_
   */
  string Money::currency() const
  {
    return currency_;
  }


  /*
   * FUNKTION unit() const
   *
   * Retunerar värdet för unit_
   */
  int Money::unit() const
  {
    return unit_;
  }


  /*
   * FUNKTION 
   *
   * Returnerar värdet för centi_
   */
  int Money::centi() const
  {
    return centi_;
  }
  

  /********** TILLDELNING **********/
 
  /*
   * FUNKTION operator=(Money rhs) &
   *
   * Tilldelar ett objekt värdet av ett annat objekt rhs.
   */
  Money& Money::operator=(Money rhs) &
  {
    if (currency_.empty())
      {
	currency_ = rhs.currency_;
	unit_ = rhs.unit_;
	centi_ = rhs.centi_;
      }
    else if ( rhs.currency_.empty() || (currency() == rhs.currency()) )
      {
	unit_ = rhs.unit_;
	centi_ = rhs.centi_;
      }
    else
      {
	throw monetary_error{"objekten måste ha samma valuta"};
      }
    return *this;
  }

  
  /********** TVÅ MONEYOBJEKT BYTER INNEHÅLL **********/

  /*
   * FUNKTION swap(Money& rhs) noexcept
   *
   * Byter innehåll på två Money objekt.
   */
  void Money::swap(Money& rhs) noexcept
  {
    std::swap(currency_, rhs.currency_);
    std::swap(unit_, rhs.unit_);
    std::swap(centi_, rhs.centi_);

  }


  /********** STEGNING **********/
 
  /*
   * FUNKTION operator++()
   *
   * Stegar upp centi_ i objektet och eventuellt även unit_ (om centi_ kommer upp
   * i 100). Retunerar sedan den förändrade strängen.
   */
  Money& Money::operator++() & noexcept // PREFIX
  {
    if ( ++(*this).centi_ == 100)
      {
	++(*this).unit_;
	(*this).centi_ = 0;
      } 
    return *this;
  }


  /*
   * FUNKTION operator++(int)
   *
   * Gör en kallelse till stegningsoperatorn ++ prefix. Retunerar kopia av objektet
   * som det var vid tillkallelse.
   */
  Money Money::operator++(int) // POSTFIX
  {
    Money temp{*this};
    ++*this;
    return temp; 
  }
 

  /*
   * FUNKTION operator--()
   *
   * Stegar ner centi_ i objektet och eventuellt även unit_ (om centi_ kommer ner
   * till 0). Retunerar sedan den förändrade strängen. Tillåter inte stegring till
   * negativa värden av unit_.
   */
  Money& Money::operator--() & noexcept // PREFIX
  {
    if (unit_ == 0 && centi_ == 0)
      {
	throw monetary_error{"Får inte ha negativa värden"};
      }
    if (--centi_ == -1)
      {
	--unit_;
	centi_ = 99;
      }
    return *this;
  }


  /*
   * FUNKTION operator--(int)
   *
   * Gör en kallelse till stegningsoperatorn -- prefix. Retunerar kopia av objektet
   * som det var vid tillkallelse. 
   */
  Money Money::operator--(int) // POSTFIX
  {
    Money temp{*this};
    --*this;
    return temp; 
  }


  /********** VALUTASAMMANSÄTTNING **********/
 
  /*
   * FUNKTION operator+(Money& lhs, Money& rhs)
   * 
   * Adderar unit() och centi() värdet på av två Money objekt och retunerarar svaret.
   * Om minst en av objekten har en currency() deklarerad retuneras även detta.
   * Fel kastas om objekten som skall adderas har olika currency() värden som inte
   * är nollsträngen.
   */
  Money Money::operator+(const Money rhs)
  {
    Money lhs{*this};
    if ( !same_currency(lhs, rhs) )
      {
	throw monetary_error("kan inte addera två olika valutor");
      }
    Money temp_money{ (lhs.unit() + rhs.unit()), (lhs.centi() + rhs.centi()) };
    if (temp_money.centi() >= 100)
      {
	temp_money.centi_ = temp_money.centi_ - 100;
	++temp_money.unit_;
      }
  
    if ( (lhs.currency().empty()) )
      {
	temp_money.currency() = rhs.currency();
      }
    else 
      {      
	temp_money.currency() = lhs.currency();
      }
  
    return temp_money;
  }


  /*
   * FUNKTION operator+=()
   *
   * Adderar unit_ och centi_ värdena för två Money objekt, *this och rhs.
   * Sparar summan i *this som returneras.
   */
  Money& Money::operator+=(Money rhs) &
  {
    return (*this = *this + rhs);
  }


  /*
   * FUNKTION operator-(Money& lhs, Money& rhs)
   * 
   * Subtraherar unit_ och centi_ värdet på av två Money objekt och retunerarar svaret.
   * Om minst en av objekten har en currency() deklarerad retuneras även detta.
   * Fel kastas om objekten som skall adderas har olika currency() värden som inte
   * är nollsträngen.
   */
  Money Money::operator-(const Money rhs)
  {
    Money lhs{*this};
    if ( !same_currency(lhs, rhs) )
      {
	throw monetary_error("kan inte subtrahera två olika valutor");
      }
    Money temp_money{ (lhs.unit() - rhs.unit()), (lhs.centi() - rhs.centi()) };
    if (temp_money.centi() < 0)
      {
	temp_money.centi_ = temp_money.centi_ + 100;
	--temp_money.unit_;
      }
    if (unit_ < 0)
      {
	throw monetary_error{"Inga negativa värden"};
      }
  
    if ( (lhs.currency().empty()) )
      {
	temp_money.currency() = rhs.currency();
      }
    else 
      {      
	temp_money.currency() = lhs.currency();
      }
  
    return temp_money;
  }


  /*
   * FUNKTION operator-=()
   * 
   * Subtraherar unit_ och centi_ värdena för *this och rhs.
   * Sparar summan i *this som returneras.
   */
  Money& Money::operator-=(Money rhs) &
  {
    return (*this = *this - rhs);
  }

  /********** IN- OCH UTMATNING **********/
 
  /*
   * FUNKTION operator<<(std::ostream& stream, const Money& op)
   *
   * Retunerar utskrift av objektet op.
   */
  ostream& operator<<(std::ostream& stream, const Money& op)
  {
    op.print(stream);
    return stream;
  }


  /*
   * FUNKTION operator>>(std::istream& stream, Money& arg)
   *
   * Läser värden från en inström och sparar dessa i objektet arg.
   * Upptäcker fel vid formatering och kastar ett monetary_error
   * om formateringen är fel.
   * Returnerar inströmmen.
   */
  istream& operator>>(std::istream& is,  Money& arg)
  {
    char c;
    bool search_flag{true};
    bool cur_flag{false};
    bool unit_flag{false};
    int unit{0};
    int centi{0};
    string cur{""};
    string centi_str;

    while (is.good() && search_flag)
      {
	c = is.get();
	if (!isspace(c))
	  {
	    search_flag = false;
	    is.putback(c);
	  }
      }
    
    if ( is.good() && isalpha(is.peek()) )
      {
	is >> cur;
	if (cur.length() != 3)
	  {
	    throw monetary_error{"inte godkänd längd på valutan"};
	  }
	cur_flag = true;
      }
    
    if (is.good() && !(is.peek() == '\n'))
      {
	/*c = is.get();
	  if (!isspace(c))
	  {
	  is.putback(c);
	  }
	*/
	if (isspace( is.peek() ))
	  {
	    c = is.get();
	    //is.ignore(1);
	  }
      }
    
    if ( is.good() && isdigit(is.peek()) )
      {
	is >> unit;

	if ( is.good() && is.peek() == '.')
	  {
	    c = is.get();
	    if ( is.good() && isdigit(is.peek()) )
	      {
		is >> centi_str;
		if (centi_str.length() > 2)
		  {
		    throw monetary_error{"inte godkänd valuta"};
		  }
		
		if (centi_str.length() == 1)
		  {
		    centi_str.push_back('0');
		  }
		
		for (unsigned i = 0; i < centi_str.length(); ++i)
		  {
		    if ( !isdigit(centi_str[i]) )
		      {
			throw monetary_error{"inte godkänd valuta"};
		      }
		  }
		centi = atoi(centi_str.c_str());
	      }
		
	    else
	      {
		is.putback(c);
	      }
	  }

	else if ( is.good() && !isspace(is.peek()) )
	  {
	    throw monetary_error{"inte godkänd valuta"};
	  }
	unit_flag = true;    
      }
    

    if ( unit_flag == false && cur_flag == false)
      {
	throw monetary_error{"inte godkänt Money objekt"};
      }
      
    
    Money{cur, unit, centi}.swap(arg);
    cout << "DU SKREV IN OBJEKTET: " << arg << '\n';
    return is;
  }



  /********** JÄMFÖRELSER **********/
 
  /*
   * FUNKTION same_currency(Money& lhs, Money& rhs)
   * 
   * Returnerar true om båda objekten har samma värde på currency_
   * eller om någon av dem inte har något värde på currency_.
   */
  bool same_currency(const Money& lhs, const Money& rhs)
  {
    return ( (lhs.currency() == rhs.currency() ) 
	     || lhs.currency().empty()
	     || rhs.currency().empty() );
  }
  
  
  /*
   * FUNKTION operator<(Money& lhs, Money& rhs) & const
   *
   * Returnerar true om det högra moneyobjektet är mindre än det
   * vänstra moneyobjektet.
   * Kastar felet monetary_error om objekten inte är av samma valuta.
   * 
   */
  bool operator<(const Money& lhs, const Money& rhs)
  {
    if ( !same_currency(lhs, rhs) )
      {
	throw monetary_error("får inte jämföra två olika valutor");
      }
    if (lhs.currency() == rhs.currency())
      {
	if (lhs.unit() == rhs.unit())
	  {
	    return (lhs.centi() < rhs.centi());
	  }
	else
	  {
	    return lhs.unit() < rhs.unit();
	  }
      }
    else
      { 
	return false;
      }
  }


  /*
   * FUNKTION operator>(Money& lhs, Money& rhs) & const
   *
   * Returnerar true om det högra moneyobjektet är större än det
   *  vänstra moneyobjektet.
   * 
   */
  bool operator>(const Money& lhs, const Money& rhs)
  {
    return ( !(lhs<rhs) && !(lhs==rhs) );
  }


  /*
   * FUNKTION operator<=(Money& lhs, Money& rhs) & const
   *
   *  Returnerar true om det högra moneyobjektet är mindre än eller
   * lika med det vänstra moneyobjektet.
   * 
   */
  bool operator<=(const Money& lhs, const Money& rhs)
  {
    return ( (lhs < rhs) || (lhs == rhs));
  }


  /*
   * FUNKTION operator>=(Money& lhs, Money& rhs) & const
   *
   * Returnerar true om det högra moneyobjektet är större än eller
   * lika med det vänstra moneyobjektet.
   * 
   */
  bool operator>=(const Money& lhs, const Money& rhs)
  {
    return ( !(lhs < rhs) );
  }


  /********** TEST AV LIKHET OCH OLIKHET **********/

  /*
   * FUNKTION operator==(Money& lhs, Money& rhs) & const 
   *
   * Retunerar true om två Money objekt är lika varandra.
   */
  bool operator==(const Money& lhs, const Money& rhs)
  {
    if ( !(same_currency(lhs, rhs)) )
      {
	throw monetary_error{"kan inte jämföra olika valutor"};
      }
    return ( lhs.unit() == rhs.unit()
	     && lhs.centi() == rhs.centi() );    
  }


  /*
   * FUNKTION operator!=(Money& lhs, Money& rhs) & const
   *
   * Retunerar true om två Money objekt inte är lika varandra.
   */
  bool operator!=(const Money& lhs, const Money& rhs)
  {
    return ( !(lhs == rhs) );
  }


} // namespace monetary
