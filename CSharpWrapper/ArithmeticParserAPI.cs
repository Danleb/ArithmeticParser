using System;
using System.Runtime.InteropServices;

namespace ArithmeticParser
{
#pragma warning disable CA1815 // Override equals and operator equals on value types
    public struct ErrorData
#pragma warning restore CA1815 // Override equals and operator equals on value types
    {
        public ErrorCode ErrorCode;
        public int ErrorStartSymbolIndex;
        public int ErrorEndSymbolIndex;
        public string Description;
    }

    /// <summary>
    /// Possible code errors in case of invalid expression input.
    /// </summary>
    public enum ErrorCode : int
    {
        SUCCESS = 0,
        UNDEFINED_ERROR = 1,
        LEXICAL_ERROR = 2,
        SYNTACTIC_ERROR = 3,
        SINGLE_CLOSING_PARENTHESIS = 4,
        SINGLE_OPENING_PARENTHESIS = 5
    }

    public class Expression : IDisposable
    {
        private IntPtr _expression;

        public double Calculate()
        {
            return 0;
        }

        public double Calculate(double [] parameters)
        {
            return 0;
        }

        public virtual void Dispose()
        {
            Dispose(true);
        }

        public void Dispose(bool isDisposed)
        {

        }

    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="arguments"></param>
    /// <returns></returns>
    //public delegate double Expression(double[] arguments);

    public static class ArithmeticParserAPI
    {
        private const string DllName = "ArithmeticParser.dll";


        //public static bool ParseExpression(out ErrorData[] errorDatas, out Expression expression, out IntPtr )
        //{

        //}

        /// <summary>
        /// Calculate value of the expression with variables.
        /// </summary>
        /// <returns></returns>        
        public static double Calculate(IntPtr expression, double[] variablesValues)
        {
            return Calculate(expression, variablesValues, variablesValues.Length);
        }

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
        [DllImport(DllName, EntryPoint = "Process", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern ErrorData[] Process(string input, out double result, out IntPtr expression);

        /// <summary>
        /// Calculate value .
        /// </summary>
        /// <returns></returns>
        [DllImport(DllName, EntryPoint = "Calculate")]
        public static extern double Calculate(IntPtr expression);

        /// <summary>
        /// Calculate value of the expression with variables.
        /// </summary>
        /// <returns></returns>
        [DllImport(DllName, EntryPoint = "CalculateWithVariables")]
        private static extern double Calculate(IntPtr expression, double[] variablesValues, int variablesCount);

        /// <summary>
        /// Delete the parsed expression from memory.
        /// </summary>
        /// <param name="expression"></param>
        [DllImport(DllName, EntryPoint = "DeleteExpression")]
        public static extern void DeleteExpression(IntPtr expression);

#pragma warning restore CA1401 // P/Invokes should not be visible
    }
}