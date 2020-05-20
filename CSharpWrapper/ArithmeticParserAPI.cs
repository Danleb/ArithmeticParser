using System.Runtime.InteropServices;

namespace ArithmeticParser
{
#pragma warning disable CA1815 // Override equals and operator equals on value types
    public struct ErrorData
#pragma warning restore CA1815 // Override equals and operator equals on value types
    {
        public int ErrorCode;
        public string Description;
    }

    public static class ArithmeticParserAPI
    {
#pragma warning disable CA1401 // P/Invokes should not be visible

        /// <summary>
        /// Parse and calculate the expression.
        /// If the expression was calculated without errors, the 
        /// ErrorData array will be zero-sized.
        /// If the expression was calculated with error, the
        /// Error data array will contain all recognized errors.
        /// </summary>
        /// <param name="input">String that contains expression for calculations</param>
        /// <param name="result">Calculated value of the expression</param>
        /// <returns>List of errors</returns>
        [DllImport("ArithmeticParser", CharSet = CharSet.Unicode)]
        public static extern ErrorData[] Process(string input, out double result);

#pragma warning restore CA1401 // P/Invokes should not be visible
    }
}