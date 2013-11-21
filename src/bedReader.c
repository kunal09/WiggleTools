// Copyright 2013 EMBL-EBI
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
// http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <stdlib.h>
#include <string.h> 

#include "wiggleIterator.h"

typedef struct bedReaderData_st {
	char  *filename;
	FILE * file;
	char * chrom;
	int stop;
} BedReaderData;

void BedReaderPop(WiggleIterator * wi) {
	BedReaderData * data = (BedReaderData *) wi->data;
	char line[5000];
	char chrom[1000];

	if (wi->done)
		return;

	if (fgets(line, 5000, data->file)) {
		sscanf(line, "%s\t%i\t%i", chrom, &wi->start, &wi->finish);
		// I like my finishes to be non inclusive...
		wi->start++;
		wi->finish++;

		// The reason for creating a new string instead of simply 
		// overwriting is that other functions may still be pointin
		// at the old label
		if (wi->chrom[0] == '\0' || strcmp(wi->chrom, chrom)) {
			wi->chrom = (char *) calloc(strlen(chrom), sizeof(char));
			strcpy(wi->chrom, chrom);
		}

		if (data->stop > 0 && (strcmp(wi->chrom, data->chrom) > 0 || (strcmp(data->chrom, wi->chrom) == 0 && wi->start > data->stop))) {
			wi->done = true;
		}
	} else {
		fclose(data->file);
		data->file = NULL;
		wi->done = true;
	}
}

void BedReaderSeek(WiggleIterator * wi, const char * chrom, int start, int finish) {
	BedReaderData * data = (BedReaderData*) wi->data;

	if (wi->done || strcmp(chrom, wi->chrom) < 0 || (strcmp(chrom, wi->chrom) == 0 && start < wi->start)) {
		if (data->file)
			fclose(data->file);
		if (!(data->file = fopen(data->filename, "r"))) {
			printf("Could not open input file %s\n", data->filename);
			exit(1);
		}
		pop(wi);
	}

	data->chrom = chrom;
	data->stop = finish;
	wi->done = false;
	while (!wi->done && (strcmp(wi->chrom, chrom) < 0 || (strcmp(chrom, wi->chrom) == 0 && wi->finish < start))) 
		pop(wi);
}

WiggleIterator * BedReader(char * filename) {
	BedReaderData * data = (BedReaderData *) calloc(1, sizeof(BedReaderData));
	data->filename = filename;
	data->stop = -1;
	if (!(data->file = fopen(filename, "r"))) {
		printf("Could not open bed file %s\n", filename);
		exit(1);
	}
	return newWiggleIterator(data, &BedReaderPop, &BedReaderSeek);
}
