extern "C" {
    __declspec(dllexport) const int INF = 2000000000;
    __declspec(dllexport) int readIntegerInLine();
    __declspec(dllexport) double readDoubleInLine();
    __declspec(dllexport) void fillArray(double* arr, int size);
    __declspec(dllexport) double getRecursiveSumHalf(double* arr, int indx1, int indx2);
    __declspec(dllexport) double getRecursiveSum(double* arr, int size, int step);
}