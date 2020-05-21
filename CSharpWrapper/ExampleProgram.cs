using ArithmeticParser;
using System;

namespace CSharpWrapper
{
    public static class ExampleProgram
    {
        public static void UsageExample(string[] args)
        {
            var input = "ln(e)^(1+1)+4(2*45/9)+sin(PI/2)";

            var errorDatas = ArithmeticParserAPI.Process(input, out var result);

            if (errorDatas.Length == 0)
            {
                Console.WriteLine($"Calculated value = {result}");
            }
            else
            {
                Console.WriteLine("Errors: ");

                foreach (var errorData in errorDatas)
                {
                    var errorName = Enum.GetName(typeof(ErrorCode), errorData.ErrorCode);

                    //Console.WriteLine($"ErrorCode #{errorData.ErrorCode}; ErrorName={errorName}");

                    Console.WriteLine($"ErrorCode #{errorData.ErrorCode}; ErrorName={errorName}; Description={errorData.Description}");
                }
            }
        }
    }
}