///////////////////////////////////////////////////////////////////////////////
// algorithms.hpp
//
// Definitions for four algorithms:
//
// run_length_encode
// longest_frequent_substring
// reformat_date
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <cctype>
#include <string.h>
#include <vector>
#include <cstring>
using namespace std;
namespace algorithms {

  // Run-length-encode the given string.
  //
  // uncompressed must be a string containing only lower-case letters or spaces.
  //
  // A run is defined as a sequence of K>2 contiguous copies of the same
  // character c.
  // For example, "aaa" is a run with K=3 and c='a'.
  // This function returns a string based on uncompressed, where every run is
  // replaced with the string
  //   COUNTc
  // where COUNT is the base-10 representation of K. Non-run characters are
  // left as-is.
  //
  // Example inputs and outputs:
  //   "aaa" -> "3a"
  //   "heloooooooo there" -> "hel8o there"
  //   "footloose and fancy free" -> "f2otl2ose and fancy fr2e"
  //
  // Throws std::invalid_argument if the string contains invalid characters.
  std::string run_length_encode(const std::string& uncompressed) {

    std::stringstream ss;

    if (uncompressed.length() == 0) {
      return ss.str();
    }

    for (int i = 0; i < uncompressed.length(); i++) {
      if (!isspace(uncompressed[i]) && !islower(uncompressed[i])) {
        throw std::invalid_argument("invalid");
      }
    }

    // grab length of input
    int n = uncompressed.length();

    // iterate through input
    for (int i = 0; i < n; i++) {

        int count = 1;

        //keep count while still same char
        while (uncompressed[i] == uncompressed[i + 1]) {
            count++;
            i++;
        }

        if (count > 1) {
            ss << count << uncompressed[i];
        }
        else {
            ss << uncompressed[i];
        }
    }

    //return stringstream and cast to string
    return ss.str();

  }

  // Returns the longest substring of text, such that every character in the
  // substring appears at least k times in text.
  // If there are ties, the substring that appears first is returned.
  std::string longest_frequent_substring(const std::string& text, unsigned k) {

    // create an empty map
    std::map<char, int> freq;

    for (int c = 0; c < text.length(); c++) {
        if (!freq.count(text[c])) {
            freq[text[c]] = 1;
        }
        else {
            freq[text[c]]++;
        }
    }

    std::string best = "";

    for (int b = 0; b < text.length(); b++) {
        for (int e = 0; e < text.length(); e++) {
            //cand << S.substr();
            auto cand = text.substr(b, e + 1);
            char c = text[b + e];

            if (freq[c] >= k) {
                if (cand.size() > best.size()) {
                    best = cand;
                }
            }
            else {
                b = b + e;
                break;
            }
        }

    }
    //std::cout << best;
    return best;
  }

  // Reformats a string containing a date into YYYY-MM-DD format.
  //
  // input may be formatted in one of four patterns:
  // 1. Y-M-D
  //    where Y, M, and D are positive integers
  // 2. M/D/Y
  //    where Y, M, and D are positive integers
  // 3. MONTH DAY, YEAR
  //    where
  //    - MONTH is a case-insensitive name of a month, ex.
  //      "january", "FEBRUARY", "March", etc.
  //    - DAY is a positive integer representing a day, e.x. "15"
  //    - YEAR is a positive integer representing a year, e.x. "2022"
  // 4. MON DAY, YEAR
  //    where
  //    - MON is a case-insensitive three-letter abbreviation of a month, ex.
  //      "jan", "FEB", "Mar", etc.
  //    - DAY is the same as above
  //    - YEAR is the same as above
  //
  // Any leading spaces or trailing spaces are ignored.
  //
  // Returns a string in strict YYYY-MM-DD format.
  //
  // Throws std::invalid argument if:
  // - input does not fit any of the four patterns
  // - MONTH is not a valid month name
  // - MON is not a valid month abbreviation
  // - DAY is not in the range [1, 31]
  // - YEAR is not in the range [1900, 2099]

  std::string monthArr[]={"january","february","march","april","may","june","july","august","september","october","november","december"};
  std::string monArr[]={"jan","feb","mar","apr","may","jun","jul","aug","sep","oct","nov","dec"};

  bool validateRange(int year, int month, int day) {

    if (year < 1900 or year > 2099) {
        throw std::invalid_argument("invalid_argument");
    }
    if (month < 1 or month > 12) {
        throw std::invalid_argument("invalid_argument");
    }
    if (day < 1 or day > 31) {
        throw std::invalid_argument("invalid_argument");
    }

    return true;
  }

  bool is_digits(const std::string& str)
    {
    	return std::all_of(str.begin(), str.end(), ::isdigit);
    }

  int checkPattern(std::string input) {

    if (input.find(" ") != std::string::npos) {
      input.erase(std::remove(input.begin(), input.end(), ','), input.end());

      std::vector<std::string> tokenList;
      std::string str(input);

      char* cstr = new char[str.length() + 1];
      std::strcpy(cstr, str.c_str());

      char* token3 = strtok(cstr, " ");

      for (int i = 0; i < 3; i++) {
          tokenList.push_back(token3);
          token3 = strtok(NULL, " ");
      }
      for (int i = 1; i < 3; i++) {
          if (!is_digits(tokenList[i])) {
              throw std::invalid_argument("invalid_argument");
          }
      }


      if (input.find("-") != std::string::npos) {

        char* token = strtok(cstr, "-");

        for (int i = 0; i < 3; i++) {
            tokenList.push_back(token);
            token = strtok(NULL, " ");
        }
        for (int i = 1; i < 3; i++) {
            if (!is_digits(tokenList[i])) {
                throw std::invalid_argument("invalid_argument");
            }
        }
      }

      if (input.find("/") != std::string::npos) {

        char* token2 = strtok(cstr, "/");

        for (int i = 0; i < 3; i++) {
            tokenList.push_back(token2);
            token2 = strtok(NULL, " ");
        }
        for (int i = 1; i < 3; i++) {
            if (!is_digits(tokenList[i])) {
                throw std::invalid_argument("invalid_argument");
            }
        }
      }

      // 1. "Y-M-D", where Y, M, and D are positive integers
      if (input.find("-") != std::string::npos) {
        return 1;

      }

      // 2. "M/D/Y", where Y, M, and D are positive integers
      if (input.find("/") != std::string::npos) {
        return 2;
      }

      std::string month = input.substr(0, input.find(" "));
      std::transform(month.begin(), month.end(), month.begin(),
          [](unsigned char c) { return std::tolower(c); });

      for (int i = 0; i < 12; i++) {
          // 3. "MONTH D, Y" where D and Y are positive integers, and MONTH is the full name of a month
          if (monthArr[i] == month) {
           return 3;
          }

          // 4. "MON D, Y" where D and Y are positive integers, and MON is the first three letters of a month name
          if (monArr[i] == month) {
           return 4;
         }
        }
      }
    return -1;
}


  std::string reformat_date(const std::string& input) {
    try{
    int pattern = checkPattern(input);

    if (pattern == -1) {
      throw std::invalid_argument("invalid");
    }

    std::string output = "";
    int year = 0;
    int month = 0;
    int day = 0;
    std::string strMonth = "";
    std::string strDay = "";


    if (pattern == 1) {
        // 1. "Y-M-D", where Y, M, and D are positive integers
        int tempIndex = 0;
        year = std::stoi(input.substr(tempIndex, input.find("-")));
        tempIndex += input.find("-") + 1;
        month = std::stoi(input.substr(tempIndex, input.find("-")));
        tempIndex += tempIndex - input.find("-") + 1;
        day = std::stoi(input.substr(tempIndex + 1, input.length()));


        if (validateRange(year, month, day)) {
            if (month >= 1 and month <= 9) {
                strMonth = '0' + std::to_string(month);
            }
            else {
                strMonth = std::to_string(month);
            }

            if (day >= 1 and day <= 9) {
                strDay = '0' + std::to_string(day);
            }
            else {
                strDay = std::to_string(day);
            }

            output = std::to_string(year) + "-" + strMonth + "-" + strDay;
            //cout << output << endl;
            return output;
        }

      }

    if (pattern == 2) {
        // 2. "M/D/Y", where Y, M, and D are positive integers
        int tempIndex = 0;
        month = std::stoi(input.substr(tempIndex, input.find("/")));
        tempIndex += input.find("/") + 1;
        day = std::stoi(input.substr(tempIndex, input.find("/")));
        tempIndex += tempIndex - input.find("/") + 1;
        year = std::stoi(input.substr(tempIndex + 1, input.length()));

        if (validateRange(year, month, day)) {
            if (month >= 1 and month <= 9) {
                strMonth = '0' + std::to_string(month);
            }
            else {
                strMonth = std::to_string(month);
            }

            if (day >= 1 and day <= 9) {
                strDay = '0' + std::to_string(day);
            }
            else {
                strDay = std::to_string(day);
            }
            output = std::to_string(year) + "-" + strMonth + "-" + strDay;
            //cout << output << endl;
            return output;
        }
      }
    if (pattern == 3) {
        // 3. "MONTH D, Y" where D and Y are positive integers, and MONTH is the full name of a month
        int tempIndex = 0;
        std::string inputMonth = input.substr(tempIndex, input.find(" "));
        std::transform(inputMonth.begin(), inputMonth.end(), inputMonth.begin(),
            [](unsigned char c) { return std::tolower(c); });

        tempIndex += input.find(" ") + 1;

        for (int i = 0; i < 12; i++) {
            if (monthArr[i] == inputMonth) {
                month = i + 1;
                break;
            }
        }

        day = std::stoi(input.substr(tempIndex, input.find(",")));
        tempIndex = input.find(",") + 1;
                string tempYear = input.substr(tempIndex, input.length());
    if (tempYear.find(',') != string::npos ){
        throw std::invalid_argument("invalid_argument");
    }
        year = std::stoi(input.substr(tempIndex, input.length()));

        if (validateRange(year, month, day)) {
            if (month >= 1 and month <= 9) {
                strMonth = '0' + std::to_string(month);
            }
            else {
                strMonth = std::to_string(month);
            }

            if (day >= 1 and day <= 9) {
                strDay = '0' + std::to_string(day);
            }
            else {
                strDay = std::to_string(day);
            }
            output = std::to_string(year) + "-" + strMonth + "-" + strDay;
            //cout << output << endl;
            return output;
        }

      }
    if (pattern == 4) {
        // 4. "MON D, Y" where D and Y are positive integers, and MON is the first three letters of a month name
        int tempIndex = 0;
        std::string inputMonth = input.substr(tempIndex, input.find(" "));
        std::transform(inputMonth.begin(), inputMonth.end(), inputMonth.begin(),
            [](unsigned char c) { return std::tolower(c); });

        tempIndex += input.find(" ") + 1;

        for (int i = 0; i < 12; i++) {
            if (monArr[i] == inputMonth) {
                month = i + 1;
                break;
            }
        }

        day = std::stoi(input.substr(tempIndex, input.find(",")));
        tempIndex = input.find(",") + 1;
        year = std::stoi(input.substr(tempIndex, input.length()));

        if (validateRange(year, month, day)) {
            if (month >= 1 and month <= 9) {
                strMonth = '0' + std::to_string(month);
            }
            else {
                strMonth = std::to_string(month);
            }

            if (day >= 1 and day <= 9) {
                strDay = '0' + std::to_string(day);
            }
            else {
                strDay = std::to_string(day);
            }
            output = std::to_string(year) + "-" + strMonth + "-" + strDay;
            return output;
        }
    }
    
  }catch(...){
          throw std::invalid_argument("invalid_argument");
        }
  }
}
