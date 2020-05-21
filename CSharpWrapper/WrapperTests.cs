using NUnit.Framework;

namespace CSharpWrapper
{
    [TestFixture]
    public class WrapperTests
    {
        [Test]
        public void ProcessExpressionTest()
        {
            var input = "1+2*3+50/100+.4^2";

        }

        [Test]
        public void CalculateExpressionTest()
        {
            var input = "1+1";
        }

        [Test]
        public void ErrorDataValidInputTest()
        {
            var input = "1+1";


        }

        [Test]
        public void ErrorDataInvalidInputTest1()
        {
            var input = "1+!";
        }
    }
}