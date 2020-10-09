/*
 Raj Chaudhari
 ECE 2036 L05
 Professor Hurley
 matrix.cc that acutally implements the operators 
*/


#include "matrix.h"
#include "complex.h"
#include <limits>
#include <iomanip>
#include <cmath>

using namespace std ;
namespace gtmath { //namespace enables to keep big projects organized


    //created initializer list that takes row and col to reffer to the private variables
   matrix::matrix(int row, int col)
        :rows(row),cols(col) 
   {
       //implementing the 2d dynamic array
      m_val = new complex*[rows]();
       
       double real = 0.0;
       double imag = 0.0;
       
       //allocates memory to the dynamic array
      for (int i = 0; i < rows; ++i) 
      {
         m_val[i] = new complex[cols]();
      }
      for (int i = 0; i < rows; i++) 
      {
         for (int j = 0; j < cols; j++)
         {
            m_val[i][j] = complex(real,imag);
         }
      }
       
   } //end initializer



    //getter for our rows and columns
   int matrix::getCol()const
   {
      return cols;
   }
   

    int matrix::getRow()const
    {
       return rows;
    }




   gtmath::matrix::matrix(const gtmath::matrix& m)
    {
        cols = m.cols; rows = m.rows; // reffering to the object m
      
        m_val = new complex *[rows];
        
        //allocating to 2d dynamic array
        for (int i = 0; i < rows; i++)
        {
            m_val[i] = new complex[cols];
        }
        
        
        //creats the 2d dynamic matrix based on the number of tows and columns we have
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                m_val[i][j] = m.m_val[i][j];

            }
        }
    }
   
    //once the 2d dynamic matrix is done being drawn, we remove the memory using the delete operator so there is no memory leak
   gtmath::matrix::~matrix() {
      for (int i = 0; i < rows; i++) {
         delete[] m_val[i];
      }
   }








    //parenthesis operator
   complex& matrix::operator()(int i, int j) const 
   {
      return m_val[i][j];
   }   
   
  
   
   //implementing the + operator to compute addition of complex numbers
   matrix gtmath::matrix:: operator+(const gtmath::matrix&a) const
   {
        gtmath::matrix m(a.rows, a.cols); //opject a's rows and columns
       
            //if the columns and the rows are the same, we compute normally
            if(a.rows == rows && a.cols == cols)
            {
               for(int i=0; i<a.rows; i++)
               {
                  for(int j=0; j<a.cols; j++)
                  {
                     m.m_val[i][j] = a.m_val[i][j] + m_val[i][j];
                  }
               
               }
            
            }
        //else we assign zeroes to the other matricies in the 2d dynamic matrix
            else
            {
               for(int i=0; i<a.rows; i++)
               {
                  for(int j=0; j<a.cols; j++)
                  {
                     m.m_val[i][j] = 0;
                  }
               }
            
            }
   
   
      return m;
   }
   
    //implements the = operator which allocates certain values in the 2d dynamic matrix
    matrix& matrix::operator=(const gtmath::matrix& m)
    {
       //it is importnt to delete prevous memory so we need to use delete operator to delete from dynamic matrix
        for (int i = 0; i < rows; ++i)
        {
             delete[] m_val[i];
        }
            delete[] m_val;
            
        m_val = new complex*[m.rows];
        //we will not reallocate back to the matrix
        for (int i = 0; i < m.rows; ++i)
        {
            m_val[i] = new complex[m.cols];
        }
        //assigning the values back into the matrix depending on the = operator and which row and column it is telling us to assign too
        for (int i = 0; i < m.rows; i++)
        {
            for (int j = 0; j < m.cols; j++)
            {
                m_val[i][j] = m.m_val[i][j];
            }
        }
        return *this;
    }
    
    //implementing the minus operator to function corretctly to subtract the complex numbers
    matrix gtmath::matrix::operator-(const gtmath::matrix& a) const //most operators are const so that we do not change any values being computer
    {
         matrix m(a.rows, a.cols); //reffering to opbejct a's rows and columns from the actual problems
        
            //we will simply subtract the the real with real and imag with imaginary. this is understood automatically from complex.cc
            if(a.rows == rows && a.cols == cols)
            {
               for(int i=0; i<a.rows; i++)
               {
                  for(int j = 0; j<a.cols; j++)
                  {
                     m.m_val[i][j] = m_val[i][j] - a.m_val[i][j]; //subtraction the operators
                  }
               }
            }
        //we create an empty matrix if there missing real or imaginary numbers
            else if(a.rows == 0 && a.cols == 0)
            {
               for(int i=0; i<a.rows; i++) //nested loop used over and over again to allocate 0's to the dynamic matrix
               {
                  for(int j=0; j<a.cols; j++)
                  {
                     m.m_val[i][j] = 0;
                  }
               }
            
            }
         return m;
    
    }
    
    //new operator overload that prints out values
   ::ostream& operator<<(::ostream& os,const gtmath::matrix& m)
   {
      double real = 0;
       
      double imag = 0;
       
      double hold = 0;
       
    //allocating values to the matrix using a nested loop
      for (int i = 0; i<m.getRow(); i++)
      {
         for (int j = 0; j<m.getCol(); j++)
         {
            imag = imag + (m.m_val[i][j]).getImg(); //storing the values of imaginary part of complex number
            real = real + (m.m_val[i][j]).getRe(); //storing values of real part of complex in the matrix
            hold = hold - (m.m_val[i][j]).getRe();
         }
      }
    
       
       double reala; double realb; double intc;
   
      reala = real;
       
      realb = modf(reala , &intc);
       
      if(hold != 0 && imag == 0)
      {
         if (realb < 0 || realb > 0)
         {
         
            for (int i=0; i<m.getRow(); i++)
            {
               for (int j=0; j<m.getCol(); j++)
               {
                   //creating precision of 4
                  cout<< fixed;
                  cout << setprecision(4) << (m.m_val[i][j]).getRe()<<" + 0.000j"; //this part will print out the matrix 7
                   
                   //we print to next line and work on next matrix if none
                   
                  
                  if (j != m.getCol() - 1)
                  {
                     cout << ", ";
                  }
                   
               }
                
                if (i !=  m.getRow())
                {
                    cout<<endl;
                }
            }//end for
         
         }//endif
          
         else if (realb == 0.0)
         {
             //nested loop will configure the matrix based on the input from the main statement.
            for (int i = 0; i <  m.getRow(); i++)
            {
               for (int j = 0; j < m.getCol(); j++)
               {
                  cout << setprecision(4) << (m.m_val[i][j]).getRe()<<" + 0.0000";
                   //this part will print out the m6 part of the main file
                
                  if (j != m.getCol() - 1)
                  {
                     cout << ",";
                  }
               }
               if (i != m.getRow())
               {
                  cout << endl;
               }
            }
         
         }//end else if
      
    }//end main if
      
      else if(real == 0 && imag == 0 && hold == 0){
         cout<<"No Matrix"<<endl;
      }
      
      else 
      {
          
         for (int i = 0; i < m.getRow(); i++)
         {
            for (int j = 0; j < m.getCol(); j++)
            {
                cout << setprecision(4) << (m.m_val[i][j]).getRe();
                //imaginary is less than zero
                
               if (m.m_val[i][j].getImg() < 0)
               {
                  cout << " - "<<setprecision(4)<<(m.m_val[i][j].getImg()*-1)<<"j";
               }
               else
               {
                  cout <<" + " <<setprecision(4) << (m.m_val[i][j]).getImg() << "j";
               }
            
               if (j != m.getCol() - 1)
               {
                  cout << ", ";
               }
            }//end for
             
             //this makes m4 output move to next line when the rows end
            if (i != m.getRow())
            {
               cout << endl;
            }
             
         }//end outer for
      
      }//end else
   
      return os;    
   }
 }




