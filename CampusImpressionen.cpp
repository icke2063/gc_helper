//============================================================================
// Name        : CampusImpressionen.cpp
// Author      : icke2063
// Version     :
// Copyright   : Your copyright notice
// Description : https://coord.info/GC453VA
//============================================================================

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <fstream>
#include <string>
#include <map>
#include <vector>

#include <algorithm>

using namespace std;


typedef std::pair<std::string, uint16_t> hist_vec_pair_type;


bool myfunc(hist_vec_pair_type const & a, hist_vec_pair_type const & b)
{
     return a.second != b.second?  a.second > b.second : a.first > b.first;
};

#define	CHARCOUNT	3
#define	ABC_SIZE	27


int main(int argc, char *argv[])
{

	fstream file;
	char cstring[5000];
	std::string input("");


	if(argc < 2)
	{
		perror("Eingabepfad angeben\n");
		exit(EXIT_FAILURE);
	}

	printf("Eingabepfad: %s\n", argv[1]);


	//open file
	file.open(argv[1], ios::in);
	if(!file.is_open())
	{
		printf("Datei %s kann nicht geoeffnet werden :(!\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	//read file
    while (!file.eof())
    {
        file.getline(cstring, sizeof(cstring));
        cout << cstring << endl;
        input.append(cstring);
    }

    file.close();


    if(input.size()%CHARCOUNT != 0)
    {
		printf("Invalid character count[%i\%(%i) = %i] :(!\n", input.size(), CHARCOUNT, input.size()%CHARCOUNT);
		exit(EXIT_FAILURE);
    }

    std::vector<std::string> text;
    typedef std::map<std::string, uint16_t> histo_map_type;
    histo_map_type histo_map;

    typedef std::vector<hist_vec_pair_type > histo_vec_type;
    histo_vec_type histo_vec;


    /* handle inpt data */
    for(int i=0;i<input.size()-CHARCOUNT-1;i+=CHARCOUNT)
    {
    	std::string tmpSubStr = input.substr(i,CHARCOUNT);

    	/* put "character" into array */
    	text.push_back(tmpSubStr);

    	/* create frequency distribution */
    	histo_map_type::iterator map_it = histo_map.find(tmpSubStr);

    	if(map_it == histo_map.end())
    	{//didn't find
    		histo_map[tmpSubStr] = 1;
    	}
    	else
    	{//found it
    		histo_map[tmpSubStr]++;
    	}

    	printf("[%i]:%s\n", i, tmpSubStr.c_str());
    }

    /* put frequency distribution into sortable container @todo maby we can do this in previous step */
    for(histo_map_type::iterator map_it = histo_map.begin();map_it != histo_map.end();++map_it)
    {
    	histo_vec.push_back(std::pair<std::string, uint16_t>(map_it->first, map_it->second));
    }

    //sort frequency distribution
    std::sort(histo_vec.begin(), histo_vec.end(), &myfunc);

//    char table[ABC_SIZE] = {
//    		'a', 'b', 'c', 'd', 'e',
//    		'f', 'g', 'h', 'i', 'j',
//    		'k', 'l', 'm', 'n', 'o',
//    		'p', 'q', 'r', 's', 't',
//    		'u', 'v', 'w', 'x', 'y',
//    		'z'
//    };

    char table[ABC_SIZE] = {
    		' ', 'E', 'N', 'T', 'A',
    		'I', 'U', 'H', 'R', 'O',
    		'S', 'D', 'M', 'K', 'C',
    		'G', 'L', 'Z', 'B', 'P',
    		'F', 'W', 'J', 'V', 'X',
    		'Y', 'q'
    };

    // create lookup table frequency distribution <> character
    typedef std::map<std::string, char> lookuptable_type;
    lookuptable_type	lookup;

    int pos=0;
    for(histo_vec_type::iterator vec_it = histo_vec.begin();vec_it != histo_vec.end();++vec_it)
    {
    	if(pos < ABC_SIZE)
    	{
    		lookup[vec_it->first] = table[pos];
    		printf("[%i]\t%s\t(%i):\t'%c'\n",pos, vec_it->first.c_str(), vec_it->second, table[pos]);
    	}
    	else
    	{
    		printf("[%i]\t%s\t(%i):\t%s\n",pos, vec_it->first.c_str(), vec_it->second, "out of range");
    	}
    	pos++;
    }

    printf("\n");

    pos=0;
    // print text by lookup table
    for(std::vector<std::string>::iterator textpos = text.begin();textpos!=text.end();++textpos )
    {

    	printf("%c", lookup[*textpos]);
    	pos++;

    	if(lookup[*textpos] == ' ' && (pos > 50))
    	{
    		printf("\n");
    		pos = 0;
    	}
    }

	return 0;
}

