/*
 * Class functions for an easier h5 read and write method.
 * Created by: Steven Walton
 * Email: walton.stevenj@gmail.com
 */
#ifndef H5RW_H
#define H5RW_H

#include <iostream>
#include <vector>
#include <string>

#include "H5Cpp.h"

using namespace H5;

class WriteH5
{
   private:
   public:
      std::string variable;
      std::string filename;
      // sets our filename and our variable name
      void setFileName(std::string name) {filename = name;};
      void setVarName(std::string name) {variable = name;};
      // Functions to be overloaded
      void writeData(std::vector<int>);
      void writeData(std::vector<float>);
};

class LoadH5
{
   private:
   public:
      std::string variable;
      std::string filename;
      // sets our filename and our variable name
      void setFileName(std::string name) {filename = name;};
      void setVarName(std::string name) {variable = name;};
      // Read functions
      std::vector<int> getDataint() const;
      std::vector<float> getDatafloat() const;
      // We now make a proxy class so that we can overload the return type and use a single
      // function to get data whether int or float. This could be made more advanced by 
      // adding more data types (such as double). 
      class Proxy
      {
         private:
            LoadH5 const* myOwner;
         public:
            Proxy( const LoadH5* owner ) : myOwner( owner ) {}
            operator std::vector<int>() const
            {
               return myOwner->getDataint();
            }
            operator std::vector<float>() const
            {
               return myOwner->getDatafloat();
            }
      };
      // Here we use the Proxy class to have a single getData function
      Proxy getData() const {return Proxy(this);}
};


#endif
