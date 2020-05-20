using ArithmeticParser;
using System;

namespace CSharpWrapper
{
    public static class ExampleProgram
    {
        public static void Main(string[] args)
        {
            var input = "1+1-2";

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
                    Console.WriteLine($"{errorData.ErrorCode}: {errorData.Description}");
                }
            }
        }
    }
}