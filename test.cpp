#include <iostream>
#include <vector>
#include <string>

#include "h5rw.h"

using namespace std;

int main()
{
   vector<int> iv;
   for (size_t i = 0; i < 10; i++)
      iv.push_back(i);
   vector<float> f;
   for (size_t i = 0; i < 10; i++)
      f.push_back(i * 0.1);

   // To write daat
   WriteH5 dta;
   dta.setFileName("testData.h5");
   dta.setVarName("IntVecData");
   dta.writeData(iv);
   dta.setVarName("FloatVecData");
   dta.writeData(f);
   dta.createGroup("/my/group/");
   dta.setVarName("/my/group/FloatVecData");
   dta.writeData(f);

   // To Load Data
   LoadH5 ldata;
   ldata.setFileName("testData.h5");
   ldata.setVarName("IntVecData");
   vector<int> idta = ldata.getData();
   ldata.setVarName("FloatVecData");
   vector<float>fdta = ldata.getData();
   ldata.setVarName("/my/group/FloatVecData");
   vector<float>gfdta = ldata.getData();
  
   return 0;
}

