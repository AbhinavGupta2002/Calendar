// In this program, valid_date() checks if the date - comprising of the year,
// month, and day - is valid or not. The function day_of_the_week() returns the
// the day of the week for a given year, month, and day. The function
// print_calender() prints out a calender for a given year and month

// NOTE: follows the Georgian Calender system

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

// print_header(year, month) prints the calendar "header"
//   for the given year/month
// notes: if month is invalid, no month line is printed
//        header is aligned for 4-digit years
// effects: produces output
void print_header(const int year, const int month) {
  if (month == 1) {
    printf("====January %d====\n", year);
  } else if (month == 2) {
    printf("===February %d====\n", year);
  } else if (month == 3) {
    printf("=====March %d=====\n", year);
  } else if (month == 4) {
    printf("=====April %d=====\n", year);
  } else if (month == 5) {
    printf("======May %d======\n", year);
  } else if (month == 6) {
    printf("=====June %d======\n", year);
  } else if (month == 7) {
    printf("=====July %d======\n", year);
  }else if (month == 8) {
    printf("====August %d=====\n", year);
  } else if (month == 9) {
    printf("===September %d===\n", year);
  } else if (month == 10) {
    printf("====October %d====\n", year);
  } else if (month == 11) {
    printf("===November %d====\n", year);
  } else if (month == 12) {
    printf("===December %d====\n", year);
  }
  printf("Su Mo Tu We Th Fr Sa\n");
}

const int SUNDAY = 0;
const int base_year = 1582;
const int base_year_jan_1 = SUNDAY;
const int max_year = 2999;

// valid_date(year, month, day) returns true if date - comprised of year, month,
//                              and day - is valid. Else, it returns false
bool valid_date(int year, int month, int day) {
  if (year < base_year || year > max_year) {
    return false;
  }
  if (month < 1 || month > 12) {
    return false;
  }
  if (day == 29 && month == 2) {
    if (year % 400 == 0) {
      return true;
    } else if (year % 100 == 0) {
      return false;
    } else if (year % 4 == 0) {
      return true;
    } else {
      return false;
    }
  } else if (month == 1 || month == 3 || month == 5 || month == 7 ||
             month == 8 || month == 10 || month == 12) {
    if (day < 1 || day > 31) {
      return false;
    } else {
      return true;
    }
  } else if (month == 2) {
    if (day < 1 || day > 28) {
      return false;
    } else {
      return true;
    }
  } else {
    if (day < 1 || day > 30) {
      return false;
    } else {
      return true;
    }
  }
}

// check_leap_year(year) returns true if the inputted year is
//                       a leap year. Else, it returns false
// requires: year is between 1589 and 2999
bool check_leap_year(int year) {
  assert(year >= base_year);
  assert(year <= max_year);
  if (year % 400 == 0) {
    return true;
  } else if (year % 100 == 0) {
    return false;
  } else if (year % 4 == 0) {
    return true;
  } else {
    return false;
  }
}

// days_in_the_month(month, year) returns the number of days
//                                in the inputted month and also considers
//                                if year is a leap year or not
// requires: month is in between 1 and 12
int days_in_the_month(int month, int year) {
  assert(month >= 1);
  assert(month <= 12);
  if (month == 2 && check_leap_year(year) == true) {
    return 29;
  } else if (month == 2) {
    return 28;
  }
  else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 ||
           month == 10 || month == 12) {
    return 31;
  } else {
    return 30;
  }
}

// day_of_the_week(year, month, day) prints out a number that represents
//                                   the day of the week for the provided
//                                   day, month, and year
// requires: year is valid
//           month is valid
//           day is valid
int day_of_the_week(int year, int month, int day) {
  assert(valid_date(year, month, day) == true);
  int total_days = 0;
  int check_year = base_year;
  int check_month = 1;
  while(check_year != year) {
    while (check_month <= 12) {
      total_days += days_in_the_month(check_month, check_year);
      ++check_month;
    }
    ++check_year;
    check_month = 1;
  }
  while(check_month != month) {
    total_days += days_in_the_month(check_month, year);
    ++check_month;
  }
  total_days += day;
  return (total_days - 1) % 7;
}

// print_calendar(year, month) prints a calender for the given month and year
// requires: year is valid
//           month is valid
void print_calendar(int year, int month) {
  assert(valid_date(year, month, 1) == true);
  int day = 1;  
  int count = 0;
  int day_week = day_of_the_week(year, month, day);
  print_header(year, month);
  while (count != day_week) {
    printf("   ");
    ++count;
  }
  if (day_week == 6) {
    printf("%2d", day);
  } else {
    printf("%2d ", day);
  }
  ++day;
  while (day <= days_in_the_month(month, year)) {
    ++day_week;
    if (day_week == 7) {
      day_week = 0;
      printf("\n");
    }
    if (day_week == 6 || day == days_in_the_month(month, year)) {
      printf("%2d", day);
    } else {
      printf("%2d ", day);
    }
    ++day;
  }
  printf("\n");
}

void assertion_tests(void) {
  assert(valid_date(2021, 1, 28));
  assert(valid_date(2000, 2, 29));
  assert(valid_date(2999, 11, 30));
  assert(valid_date(1589, 1, 31));
}

int main(void) {
  assertion_tests();
  while (1) {
      int year = 0;
      int month = 0;
      scanf("%d", &year);
      int retval = scanf("%d", &month);
    if (retval != 1) {
      break;
    }
      printf("\n");
    print_calendar(year, month);
      printf("\n");
  }
}
