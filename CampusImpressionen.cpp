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

    std::vector<std::string> text;
    typedef std::map<std::string, uint16_t> histo_map_type;
    histo_map_type histo_map;

    typedef std::vector<hist_vec_pair_type > histo_vec_type;
    histo_vec_type histo_vec;


    /* handle inpt data */
    for(int i=0;i<input.size()-2;i+=3)
    {
    	/* put "character" into array */
    	text.push_back(input.substr(i,3));

    	/* create frequency distribution */
    	histo_map_type::iterator map_it = histo_map.find(input.substr(i,3));

    	if(map_it == histo_map.end())
    	{//didn't find
    		histo_map[input.substr(i,3)] = 1;
    	}
    	else
    	{//found it
    		histo_map[input.substr(i,3)]++;
    	}

    	printf("[%i]:%s\n", i, input.substr(i,3).c_str());
    }

    /* put frequency distribution into sortable container @todo maby we can do this in previous step */
    for(histo_map_type::iterator map_it = histo_map.begin();map_it != histo_map.end();++map_it)
    {
    	histo_vec.push_back(std::pair<std::string, uint16_t>(map_it->first, map_it->second));
    }

    //sort frequency distribution
    std::sort(histo_vec.begin(), histo_vec.end(), &myfunc);

//    char table[26] = {
//    		'a', 'b', 'c', 'd', 'e',
//    		'f', 'g', 'h', 'i', 'j',
//    		'k', 'l', 'm', 'n', 'o',
//    		'p', 'q', 'r', 's', 't',
//    		'u', 'v', 'w', 'x', 'y',
//    		'z'
//    };

    char table[26] = {
    		' ', 'e', 'n', 'i', 's',
    		'r', 'a', 't', 'd', 'h',
    		'u', 'l', 'c', 'g', 'm',
    		'o', 'b', 'w', 'f', 'k',
    		'z', 'p', 'v', 'j', 'y',
    		'x'
    };

    // create lookup table frequency distribution <> character
    typedef std::map<std::string, char> lookuptable_type;
    lookuptable_type	lookup;

    int pos=0;
    for(histo_vec_type::iterator vec_it = histo_vec.begin();vec_it != histo_vec.end();++vec_it)
    {
    	lookup[vec_it->first] = table[pos];
    	printf("[%i]\t%s\t(%i):\t%c\n",pos, vec_it->first.c_str(), vec_it->second, table[pos]);
    	pos++;
    }

    printf("\n");

    // print text by lookup table
    for(std::vector<std::string>::iterator textpos = text.begin();textpos!=text.end();++textpos )
    {
    	printf("%c", lookup[*textpos]);
    }

	return 0;
}

