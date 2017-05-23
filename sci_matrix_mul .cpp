extern "C"{ 
#include "api_scilab.h"
#include "Scierror.h"

int sci_matrix_mul(char *fname, unsigned long fname_len)
{
	SciErr sciErr;

 	int m1 = 0, n1 = 0;
    int *piAddressVarOne = NULL;
    double *newMatrix1OfDouble = NULL;

    int m2 = 0, n2 = 0;
    int *piAddressVarTwo = NULL;
    double *newMatrix2OfDouble = NULL;

    double *ResultMatrixOfDouble = NULL;

 	CheckInputArgument(pvApiCtx, 2, 2);
    CheckOutputArgument(pvApiCtx, 1, 1);

    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddressVarOne);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    if (!isDoubleType(pvApiCtx, piAddressVarOne) ||  isVarComplex(pvApiCtx, piAddressVarOne))
   	{
        Scierror(999, "%s: Wrong type for input argument #%d: A real matrix expected.\n", fname, 1);
        return 0;
    }

    sciErr = getMatrixOfDouble(pvApiCtx, piAddressVarOne, &m1, &n1, &newMatrix1OfDouble);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddressVarTwo);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    if (!isDoubleType(pvApiCtx, piAddressVarOne) ||  isVarComplex(pvApiCtx, piAddressVarOne))
   	{
        Scierror(999, "%s: Wrong type for input argument #%d: A real matrix expected.\n", fname, 1);
        return 0;
    }

    sciErr = getMatrixOfDouble(pvApiCtx, piAddressVarOne, &m2, &n2, &newMatrix2OfDouble);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    if ((n1 != m2))
    {
        Scierror(999, "%s: Wrong size for input arguments: Expected mxn nxp.\n", fname, 1);
        return 0;
    }
   
   	ResultMatrixOfDouble = (double*)malloc(sizeof(double) * m1 * n2);
    
   	int sum;
    int c, d, k;
    for (c = 0; c < m1; c++) {
      for (d = 0; d < n2; d++) {
        for (k = 0; k < n1; k++) {
          sum = sum + newMatrix1OfDouble[m1 * c + k] * newMatrix2OfDouble[m2 * k + d];
        }
        ResultMatrixOfDouble[m1 * c + d] = sum;
        sum = 0;
      }
    }
    
    free(newMatrix1OfDouble);
    free(newMatrix2OfDouble);
    
    sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 1, m1, n2, ResultMatrixOfDouble);
    free(ResultMatrixOfDouble);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;

    return 0;
}
}