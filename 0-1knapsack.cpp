#include <iostream>
using namespace std;

int SubsetSum(int set[], int n, int W)
{

  int M[n + 1][W + 1];

  for(int w = 0; w <= W; w++)
    M[0][w] = 0;

  for(int i = 1; i <= n; i++)
    for(int w = 0; w <= W; w++)
      if (w < set[i-1])
      {
        M[i][w] = M[i-1][w];
      }
      else
      {
        M[i][w] = max(M[i - 1][w], (set[i - 1] + M[i - 1][w - set[i - 1]]));
      }

  //--- Printing the array M
  cout << "Final Iteration:\n";
  for(int i = 0; i <= n; i++)
  {

    for(int j = 0; j <= W; j++)
      cout << M[i][j] << " ";
    cout << endl;
  }
  cout << endl;
  
  return M[n][W];
}


int main()
{

  int n, W;
  cout << "\nEnter the number of elements in set: ";
  cin >> n;
  int set[n];
  cout << "Enter the set elements: ";
  for(int i = 0; i < n; i++)
    cin >> set[i];
  cout << "Enter the sum: ";
  cin >> W;
  cout << endl;
  cout << SubsetSum(set, n, W) << " is the optimum solution value.\n";

  cout << endl;
  return 0;

}
