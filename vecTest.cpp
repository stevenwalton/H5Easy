#include <iostream>
#include <vector>
#include "H5Easy.h"
#include "H5Cpp.h"

using namespace std;
using namespace H5;

#define dim1 5
#define dim2 3
int main()
{
   vector<vector<float> > v(dim1, vector<float>(dim2));
   for ( size_t i = 0; i < dim1; ++i )
      for ( size_t j = 0; j < dim2; ++j )
         v[i][j] = 3.;
   //for ( size_t i = 0; i < dim1; ++i )
   //{
   //   for ( size_t j = 0; j < dim2; ++j )
   //      cout << v[i][j] << " ";
   //   cout << endl;
   //}
   cout << "v is shape: (" << v.size() << "," << v[0].size() <<")" << endl;
   WriteH5 dta;
   dta.setFileName("dim.h5");
   dta.setVarName("vecvecdouble");
   dta.writeData(v);
   cout << "Done writing!\tStarting read" << endl;
   
   //H5std_string FILE_NAME("dim.h5");
   //H5File file(FILE_NAME, H5F_ACC_RDONLY);
   //DataSet dataset = file.openDataSet("5x2Int");
   ////hid_t file = H5Fopen("dim.h5", H5F_ACC_RDONLY, H5P_DEFAULT);
   ////hid_t dset = H5Dopen(file, "5x2Int", H5P_DEFAULT);
   ////hid_t dspace = H5Dget_space(dset);
   //DataType datatype = dataset.getDataType();
   //DataSpace dataspace = dataset.getSpace();
   //int rank= dataspace.getSimpleExtentNdims(); // gives rank
   ////cout << rank << endl;
   ////int npts = dataspace.getSelectElemNpoints();
   ////cout << npts << endl;
   //hsize_t dims[rank];
   ////H5Sget_simple_extent_dims(dataspace, dims, NULL);
   //int y = dataspace.getSimpleExtentDims(dims);
   //cout << y << endl;
   //cout << dims[0] << " , " << dims[1] << endl;
   //H5T_class_t classt = datatype.getClass();
   //cout << "classt: " << classt << endl;
   //IntType itype = dataset.getIntType();
   //H5std_string order_string;
   //H5T_order_t order = itype.getOrder(order_string);
   //size_t size = itype.getSize();
   //cout << size << endl;
   //cout << order << endl;

   //dataspace.close();
   //datatype.close();
   //dataset.close();
   //file.close();

   LoadH5 data;
   data.setFileName("dim.h5");
   data.setVarName("vecvecdouble");
   vector<vector<float> > vv = data.getData();
   cout << "Data is read" << endl;
   for ( size_t i = 0; i < dim1; ++i )
   {
      for ( size_t j = 0; j < dim2; ++j )
         cout << vv[i][j] << "\t";
      cout << endl;
   }

   return 0;
}
