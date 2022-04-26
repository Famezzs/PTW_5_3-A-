#include "pch.h"
#include "CppUnitTest.h"
#include "../PTW_3_3(A)/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UTPTW53A
{
	TEST_CLASS(UTPTW53A)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::IsTrue(Sort("base2"));
		}
	};
}
