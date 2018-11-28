

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
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
   
   public void testIsValid()
   {
        UrlValidator urlVal = new UrlValidator(null, null,
                UrlValidator.ALLOW_ALL_SCHEMES);
       
        String[][] validUrlParts = {validSchemes,
                                   validAuthorities,
                                   validPorts,
                                   validPaths,
                                   validQueries};

        String[][] invalidUrlParts = {invalidSchemes,
                                      invalidAuthorities,
                                      invalidPorts,
                                      invalidPaths,
                                      invalidQueries};

        for (int scheme = 0; scheme < validScheme.length; scheme++) {
            for (int authority = 0; authority < validAuthority.length;
                    authority++) {
                for (int port = 0; port < validPort.length; port++) {
                    for (int path = 0; path < validPath.length; path++) {
                        for (int query = 0; query < validQuery.length;
                                query++) {
                            assertTrue(urlVal.isValid(validUrlParts[0][scheme] +
                                                validUrlParts[1][authority] +
                                                validUrlParts[2][port] +
                                                validUrlParts[3][path] +
                                                validUrlParts[4][query]));

                    
                                }
                    }

                }

            }
        }
        
   }
  
    String[] validSchemes = {"http://",
                             "https://",
                             "ftp://",
                             "foo://",
                             "test://"};
    String[] invalidSchemes = {"",
                               "http:",
                               "https//",
                               "ftp:/",
                               "foo://"};

    String[] validAuthorities = {"www.google.com",
                                 "172.217.0.36",
                                 "flip3.engr.oregonstate.edu",
                                 "128.193.36.41",
                                 "oregonstate.instructure.com"};

    String[] invalidAuthorities = {".google.com",
                                   "123.456.789.101",
                                   "flip3.engr.oregonstate.edu.",
                                   "111.111.111.111.111",
                                   "oregonstate.instructure.c"};

    String[] validPorts = {"",
                           ":0",
                           ":65535",
                           ":80",
                           ":12345"};

    String[] invalidPorts = {":eighty",
                             ":99999",
                             ":",
                             ":-100",
                             ":port"};

    String[] validPaths = {"",
                           "/foo/bar/",
                           "/support/release-notes/android",
                           "/FinalProject/URLValidatorInCorrect/test/",
                           "/courses/1692917/assignments/7334043"};

    String[] invalidPaths = {"/..",
                             "/../",
                             "/#",
                             "/#/../this/should/not/work",
                             "/#testing"};

    String[] validQueries = {"",
                             "?key=value",
                             "?key1=value1&key2=value2",
                             "?q=valid+url+queries",
                             "?testing=rad"};

    String[] invalidQueries = {"?:",
                               "?key=?",
                               "?@=me",
                               "?[]",
                               "?:?"};       

    public static void main(String[] argv) {

        test.testIsValid();
    }

}
