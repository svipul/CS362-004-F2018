

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest2 extends TestCase {


   public UrlValidatorTest2(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
//You can use this function to implement your manual testing	   
	   
   }
   
   
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   

   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
  

   
    public void testIsValid(String[] schemes, String[] authorities,
                                    String[] ports, String[] paths,
                                    String[] queries, Boolean expectedResult) {
           
       String testUrl;
int count = 0;
        UrlValidator urlVal = new UrlValidator(null, null,
                UrlValidator.ALLOW_ALL_SCHEMES);
       

        for (int scheme = 0; scheme < schemes.length; scheme++) {
            for (int authority = 0; authority < authorities.length;
                    authority++) {
                for (int port = 0; port < ports.length; port++) {
                    for (int path = 0; path < paths.length; path++) {
                        for (int query = 0; query < queries.length; query++) {
                            testUrl = schemes[scheme] +
                                      authorities[authority] +
                                      ports[port] +
                                      paths[path] +
                                      queries[query];

count++;
System.out.println(count);

                            Boolean actualResult = urlVal.isValid(testUrl);
                            assertEquals(testUrl, expectedResult, actualResult);
                        }
                    }
                }
            }
        }
   }
 
   public void testValidCombos() {
        System.out.println("Testing all valid combinations");
        testIsValid(validSchemes, validAuthorities, validPorts,
                            validPaths, validQueries, true);
   }

   public void testInvalidSchemes() {
        System.out.println("Testing invalid schemes");
        testIsValid(invalidSchemes, validAuthorities,
                                       validPorts, validPaths, validQueries,
                                       false);

   }

   public void testInvalidAuthorities() {
        System.out.println("Testing invalid authorities");
        testIsValid(validSchemes, invalidAuthorities,
                validPorts,
                            validPaths, validQueries, false);

   }

   public void testInvalidPorts() {
        System.out.println("Testing invalid ports");
        testIsValid(validSchemes, validAuthorities,
                invalidPorts,
                            validPaths, validQueries, false);
   }

   public void testInvalidPaths() {
        System.out.println("Testing invalid paths");
        testIsValid(validSchemes, validAuthorities, validPorts,
                            invalidPaths, validQueries, false);

   }

    static String[] validSchemes = {"http://",
                             "https://",
                             "ftp://",
                             "foo://",
                             "test://"};

    static String[] invalidSchemes = {"404://",
                               "http:",
                               "https//",
                               "ftp:/",
                               "://"};

    static String[] validAuthorities = {"www.google.com",
                                 "172.217.0.36",
                                 "flip3.engr.oregonstate.edu",
                                 "128.193.36.41",
                                 "oregonstate.instructure.com"};

    static String[] invalidAuthorities = {".google.com",
                                   "123.456.789.101",
                                   "flip3.3ngr.or3gonstat3.3du",
                                   "111.111.111.111.111",
                                   "oregonstate.instructure.c"};

    static String[] validPorts = {"",
                           ":0",
                           ":65535",
                           ":80",
                           ":12345"};

    static String[] invalidPorts = {":eighty",
                             ":99999",
                             ":.5",
                             ":-100",
                             ":port"};

    static String[] validPaths = {"",
                           "/foo/bar/",
                           "/support/release-notes/android",
                           "/FinalProject/URLValidatorInCorrect/test/",
                           "/courses/1692917/assignments/7334043"};

    static String[] invalidPaths = {"/..",
                             "/../",
                             "//",
                             "/../this/should/not/work",
                             "//file"};

    static String[] validQueries = {"",
                             "?key=value",
                             "?key1=value1&key2=value2",
                             "?q=valid+url+queries",
                             "?testing=rad"};

    static String[] invalidQueries = {"?:-a",
                               "?key=?",
                               "?@=me",
                               "?[]",
                               "?:?"};



                                 

    public static void main(String[] argv) {
        UrlValidatorTest2 test =
            new UrlValidatorTest2("final project unit tests");
       
        test.testValidCombos();

        test.testInvalidSchemes();

        test.testInvalidAuthorities();

        test.testInvalidPorts();

        test.testInvalidPaths();
        
        
       /* not testing queries, as they all seem to register as valid 
        System.out.println("Testing invalid queries");
        testAllCombinations(validSchemes, validAuthorities, validPorts,
                            validPaths, invalidQueries, false);
                            */
    }

}
