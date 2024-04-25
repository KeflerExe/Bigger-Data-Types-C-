In different fields of science there is a need to work with very big, or very small numerical values. New prefixes have recently been defined to name the
multiples and submultiples of any unit of the International System of Weights and Measures
With this code ata types in C++ language to handle values very large numerics, exceeding the representation range of the defined data types
in standard language. To do this, the generic data type BigInt<size_t Base> is defined.
represents integers using positional notation. In this numbering system,
The value of a digit depends on its relative position and the Base, which determines the number of
digits needed to write any number. By default, the decimal system will be used
(base 10), although it is also common to use the binary (base 2), octal (base 8) and
hexadecimal (base 16)
