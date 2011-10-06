/* vi:set ts=8 sts=8 sw=8:
 *
 * Practical Music Search
 * Copyright (c) 2006-2011  Kim Tore Jensen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "songlist.h"
#include <stdlib.h>

Songlist::Songlist()
{
	readonly = false;
	playlist = false;
	version = -1;
}

Songlist::~Songlist()
{
	clear();
}

Song * Songlist::operator[] (unsigned int spos)
{
	if (spos >= songs.size())
		return NULL;
	
	return songs[spos];
}

void Songlist::add(Song * song)
{
	if (!song)
		return;

	/* Replace a song within this list */
	if (song->pos != -1 && song->pos < (long)songs.size())
	{
		delete songs[song->pos];
		songs[song->pos] = song;
	}
	else
	{
		songs.push_back(song);
	}
}

void Songlist::clear()
{
	vector<Song *>::iterator i;
	for (i = songs.begin(); i != songs.end(); ++i)
		delete *i;
	songs.clear();
}

size_t Songlist::randpos()
{
	size_t r = 0;
	while (r < size())
		r += rand();
	r %= size() - 1;
	return r;
}

void Songlist::truncate(unsigned long length)
{
	while (songs.size() > length)
	{
		delete songs[songs.size()-1];
		songs.pop_back();
	}

	songs.reserve(length);
}

size_t Songlist::find(long hash, size_t pos)
{
	size_t it;
	for (it = 0; it < songs.size(); ++it)
		if (songs[it]->fhash == hash)
			return it;

	return string::npos;
}
