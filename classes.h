void printReceipt(vector<MenuItem> &m, double subtotal)
{
  ofstream outfile; 
  
  cout << fixed << setprecision(2);//set doubles to 2 decimal places
  cout << "RECEIPT:" << endl; 

  outfile.open("RECEIPT.txt");
    if (outfile.is_open())
    {
      outfile << "Receipt: " << endl;
      
    }
  outfile.close();
  system("RECEIPT.txt");
  
}

