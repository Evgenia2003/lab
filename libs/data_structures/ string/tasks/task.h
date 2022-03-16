#ifndef UNTITLED_TASK_H
#define UNTITLED_TASK_H

#include "libs/data_structures/ string/string_.h"

void assertString(const char *expected, char *got,
                  char const *fileName, char const *funcName,
                  int line) {
    if (strcmp_(expected, got)) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, fprintf(stderr, "Expected: \"%s\"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    } else
        fprintf(stderr, "%s - OK\n", funcName);
}

//task1
void removeNonLetters(char *s) {
    char *endSource = getEndOfString(s);
    char *destination = copyIf(s, endSource, s, isgraph);
    *destination = '\0';
}

void test_removeNonLetters1() {
    char s[] = " H e l l o ";
    removeNonLetters(s);
    ASSERT_STRING("Hello", s);
}

void test_removeNonLetters2() {
    char s[] = "Hello";
    removeNonLetters(s);
    ASSERT_STRING("Hello", s);
}

void test_removeNonLetters3() {
    char s[] = "      ";
    removeNonLetters(s);
    ASSERT_STRING("", s);
}

void test_removeNonLetters() {
    test_removeNonLetters1();
    test_removeNonLetters2();
    test_removeNonLetters3();
}

//task2
void removeExtraSpaces(char *s) {
    char *begin = s;
    char *destination = begin;
    char last = *begin;

    while (*begin != '\0') {
        if (*begin != last || last != ' ') {
            *destination = *begin;
            destination++;
        }
        last = *begin;
        begin++;
    }
}

void test_removeExtraSpaces1() {
    char string[] = "        ";
    removeExtraSpaces(string);
    ASSERT_STRING("        ", string);
}

void test_removeExtraSpaces2() {
    char string[] = "Hello";
    removeExtraSpaces(string);
    ASSERT_STRING("Hello", string);
}

void test_removeExtraSpaces3() {
    char string[] = "Hello, World!";
    removeExtraSpaces(string);
    ASSERT_STRING("Hello, World!", string);
}

void test_removeExtraSpaces() {
    test_removeExtraSpaces1();
    test_removeExtraSpaces2();
    test_removeExtraSpaces3();
}

//task3
typedef struct WordDescriptor {
    char *begin; // позиция начала слова
    char *end; // позиция первого символа, после последнего символа слова
} WordDescriptor;

bool getWord(char *beginSearch, wordDescriptor *word) {
    word->begin = findNonSpace_(beginSearch);
    if (*word->begin == '\0')
        return false;
    word->end = findSpace_(word->begin);

    return true;
}

void digitToStart(wordDescriptor word) {
    char *endStringBuffer = copy_(word.begin, word.end, stringBuffer);
    char *recPosition = copyIf_(endStringBuffer - 1, stringBuffer - 1, word.begin, isdigit);
    copyIfReverse_(stringBuffer, endStringBuffer, recPosition, isalpha);
}

void reverseDigitToStart(wordDescriptor word) {
    char *endStringBuffer = copy_(word.begin, word.end, stringBuffer);
    char *recPosition = copyIfReverse_(endStringBuffer - 1, stringBuffer - 1, word.begin, isdigit);
    copyIf_(stringBuffer, endStringBuffer, recPosition, isalpha);
}

bool getWordReverse(char *rbegin, const char *rend, wordDescriptor *word) {
    word->begin = findNonSpaceReverse_(rbegin, rend);
    if (word->begin == rend)
        return false;
    word->end = findNonSpaceReverse_(word->begin, rend);

    return true;
}

//task4
char spaceInsteadDigits(char *begin) {
    char *endSource = getEndOfString(begin);
    char *startStringBuffer = stringBuffer;
    char *endStringBuffer = copy_(begin, endSource, stringBuffer);
    *endStringBuffer = '\0';

    while (*startStringBuffer != '\0') {
        if (isalpha(*startStringBuffer))
            *begin++ = *startStringBuffer;
        else if (isdigit(*startStringBuffer)) {
            unsigned char a = *startStringBuffer - CODE_ASCII;
            while (a--)
                *begin++ = ' ';
        }
        startStringBuffer++;
    }
    *begin = '\0';
}

//task5
int areWordsEqual(wordDescriptor w1, wordDescriptor w2) {
    return strcmp_(w1.begin, w2.begin);
}

void replace(char *begin, char *replacement, char *necessary) {
    size_t sizeW1 = strlen_(replacement);
    size_t sizeW2 = strlen_(necessary);
    wordDescriptor word1 = {replacement, replacement + sizeW1};
    wordDescriptor word2 = {necessary, necessary + sizeW2};

    char *startStringBuffer;
    if (sizeW1 >= sizeW2)
        startStringBuffer = begin;
    else {
        copy_(begin, getEndOfString(begin), stringBuffer);
        startStringBuffer = begin;
    }

    wordDescriptor readWord;
    while (getWord(begin, &readWord)) {
        if (areWordsEqual(word1, readWord) != 0)
            startStringBuffer = copy_(word2.begin, word2.end, startStringBuffer);
        else
            startStringBuffer = copy_(readWord.begin, readWord.end, startStringBuffer);

        *startStringBuffer++ = ' ';
        begin = readWord.end;
    }

    *(--startStringBuffer) = '\0';
}

//task6
bool isOrderedWords(char *begin) {
    wordDescriptor w1;
    if (!getWord(begin, &w1))
        return true;
    begin = w1.end;
    wordDescriptor w2;
    while (getWord(begin, &w2)) {
        if (areWordsEqual(w1, w2) > 0)
            return false;
        begin = w2.end;
        w1.begin = w2.begin;
        w1.end = w2.end;
    }

    return true;
}

//task7
typedef struct BagOfWords {
    WordDescriptor words[MAX_N_WORDS_IN_STRING];
    size_t size;
} BagOfWords;

void getBagOfWords(bagOfWords *bag, char *begin) {
    bag->size = 0;
    wordDescriptor readWord;
    while (getWord(begin, &readWord)) {
        bag->words[bag->size++] = readWord;

        begin = readWord.end;
    }
}

//task8
bool isPalindrome(WordDescriptor word) {
    while ((word.end - word.begin) > 0) {
        if (*word.begin != *(word.end - 1))
            return 0;
        word.end--, word.begin++;
    }
    return 1;
}

int countOfPalindromes(char *s) {
    char *readStr = s;
    WordDescriptor word;
    int countPalindromes = 0;
    while (getWord_(readStr, &word)) {
        countPalindromes += isPalindrome(word);
        readStr = word.end;
    }
    return countPalindromes;
}

//task9
void alternationWordsOfTwoStrings(char *s, char *s1, char *s2) {
    WordDescriptor word1, word2;
    bool isW1Found, isW2Found;
    char *beginSearch1 = s1, *beginSearch2 = s2;
    char *sRes = s;
    while ((isW1Found = getWord(beginSearch1, &word1)), (isW2Found = getWord(beginSearch2, &word2)),
            isW1Found || isW2Found) {
        if (isW1Found) {
            sRes = copy(word1.begin, word1.end, sRes);
            *sRes++ = ' ';
            beginSearch1 = word1.end;
        }
        if (isW2Found) {
            sRes = copy(word2.begin, word2.end, sRes);
            *sRes++ = ' ';
            beginSearch2 = word2.end;
        }
    }
    if (sRes != s)
        sRes--;
    *sRes = '\0';
}

//task10
void flipWords(char *s) {
    *copy(s, getEndOfString(s), stringBuffer) = '\0';
    getBagOfWords(&_bag, stringBuffer);
    char *copyS = s;
    for (int i = _bag.size - 1; i >= 0; --i) {
        string = copy(_bag.words[i].begin, _bag.words[i].end, s);
        *s++ = ' ';
    }
    if (s != copyS)
        --s;
    *s = '\0';
}

void test_flipWords1() {
    char s[MAX_STRING_SIZE] = "";
    flipWords(s);
    ASSERT_STRING("", s);
}

void test_flipWords2() {
    char s[MAX_STRING_SIZE] = "hello";
    flipWords(s);
    ASSERT_STRING("hello", s);
}

void test_flipWords3() {
    char s[MAX_STRING_SIZE] = "hello world!";
    flipWords(s);
    ASSERT_STRING("world! hello", s);
}

void test_flipWords() {
    test_flipWords1();
    test_flipWords2();
    test_flipWords3();
}

//task11


#endif

