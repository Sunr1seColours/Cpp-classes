# Array, BigInteger, Matrix and Vector classes
## Array
My realizaton of std::array container.\
There are also methods which std::array type has. But there are some another methods, such as *GetSize*, *GetRank* and *GetNumElements*.\
#### GetSize
Returns size of array.

#### GetRank
Returns amount of dimensions in array.

#### GetNumElements
Returns total amount of elements.

## BigInteger
Sometimes you need to make operations with number which is greater than 2^64. And this class is good for it.\
Every BigInteger object contains std::vector of it's digits. Each element of std::vector is three-digit number. But total amount of digits must be less than 30000. 
In another case exception will be generated.

## Matrix
Class which represents matrix. It has methods to access elements, make arithmetical operations with matrix *(such as addition, substration, multiplication, multiplication by number
and division by number)*, operations for check equality, IO operations, transpose matrix, get trace, get algebraic addition, find determinant and inverse matrix.

## Vector
My realization of std::vector container.\
It has the same methods as std::vector has. Also there is an Iterator class to make access via pointers in Vector.
