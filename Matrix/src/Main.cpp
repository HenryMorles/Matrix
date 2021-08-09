#include "Matrix.h"
#include "MyException.h"
#include "Loader.h"
#include "Sort.h"
#include "Container.h"


int main() {
	std::vector<std::vector<int>> arr01{ {1,2,3},{1,222,3},{1,2,3} };
	std::vector<std::vector<int>> arr02{ {1,2,1},{1,2,2},{1,2,1} };
	std::vector<std::vector<int>> arr03{ {1,2,6},{1,20,6},{1,2,10} };
	Matrix matrix01(arr01);
	Matrix matrix02(arr02);
	Matrix matrix03(arr03);

	Container<Matrix> MatrixCont;
	MatrixCont.PushBack(matrix01);
	MatrixCont.PushBack(matrix02);
	MatrixCont.PushBack(matrix03);

	MatrixCont.LoadOperations("C:\\Users\\Msi\\Desktop\\Fox\\Task 9. Templates, SmartPtrs, Functors\\Task 9. Templates, SmartPtrs, Functors\\Task 9. Templates, SmartPtrs, Functors\\file.txt", 4);

	Matrix TempMatrix1(MatrixCont.Calculate("C:\\Users\\Msi\\Desktop\\Fox\\Task 9. Templates, SmartPtrs, Functors\\Task 9. Templates, SmartPtrs, Functors\\Task 9. Templates, SmartPtrs, Functors\\file.txt"));
	TempMatrix1.PrintMatrix();

	/*MyFunctor functor;
	functor("+", 2);
	Matrix TempMatrix2(MatrixCont.PerformOperation(matrix01, matrix02, functor.GetOperator(2)));*/
	//TempMatrix2.PrintMatrix();

	return 0;
}