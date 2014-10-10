/*
 * FILNAMN:       Monetary.h
 * LABORATION:    Lab 2
 * PROGRAMMERARE: Björn Wilke, 870617-0415, Ii#a
 *                Malin Aspelin, 910527-5524, FyN3
 * DATUM:         2014-10-10
 *
 * BESKRIVNING 
 * Filen innehåller deklarationer av alla funktioner som är
 * skrivna för att hantera klassen Money.
 * 
 */

#ifndef MONETARY_H
#define MONETARY_H

#include <string>
#include <iostream>
#include <stdexcept>
#include <cctype>


namespace monetary
{
  class Money
  {
  public:

    /********** KONSTRUKTORER OCH DESTRUKTOR **********/
    Money(const int = 0, const int = 0);
    Money(const std::string&, const int = 0, const int = 0);
    Money(const Money&);
    ~Money();
    
    /********** FUNKTIONER **********/
    void print(std::ostream&) const;
    std::string currency() const;
    int unit() const;
    int centi() const;

    /********** TILLDELNING **********/
    Money& operator=(Money rhs) &; 

    /********** TVÅ MONEYOBJEKT BYTER INNEHÅLL **********/
    void swap(Money&) noexcept;
    
    /********** STEGNING **********/
    Money& operator++() & noexcept;  // PREFIX
    Money operator++(int);          // POSTFIX
    Money& operator--() & noexcept;  // PREFIX
    Money operator--(int);          // POSTFIX

    /********** VALUTASAMMANSÄTTNING **********/
    Money operator+(const Money rhs);
    Money& operator+=(Money rhs) &;
    Money operator-(const Money rhs);
    Money& operator-=(Money rhs) &;

    
  private:
    /********** KLASSEN MONEY:S POSTER **********/
    std::string currency_{""};
    int unit_{0}; // >0
    int centi_{0}; // >0  
  };


  /********** IN- OCH UTMATNING **********/
  std::ostream& operator<<(std::ostream&, const Money&);
  std::istream& operator>>(std::istream&, Money&);

  
  /********** JÄMFÖRELSER **********/
  bool same_currency(const Money&, const Money&);
  bool operator<(const Money& lhs, const Money& rhs);
  bool operator>(const Money& lhs, const Money& rhs);
  bool operator<=(const Money& lhs, const Money& rhs);
  bool operator>=(const Money& lhs, const Money& rhs);


  /********** TEST AV LIKHET OCH OLIKHET **********/
  bool operator==(const Money& lhs, const Money& rhs);
  bool operator!=(const Money& lhs, const Money& rhs);

  class monetary_error : public std::logic_error
    {
    public:
      explicit monetary_error(const std::string& what_arg) noexcept
	: std::logic_error{what_arg} {}

      explicit monetary_error(const char* what_arg) noexcept
	: std::logic_error{what_arg} {}
    };
  
  
} // namespace monetary

#endif

