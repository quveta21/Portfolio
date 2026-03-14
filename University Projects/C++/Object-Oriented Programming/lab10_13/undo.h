#pragma once

#include "repository.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
private:
	MedicamentRepo& repo;
	//Medicament last;
public:
	UndoAdauga(MedicamentRepo& repo) : ActiuneUndo(), repo{ repo } {}

	void doUndo() override {
		repo.remove((int)repo.getAll().size());
	}
};

class UndoSterge : public ActiuneUndo {
private:
	MedicamentRepo& repo;
	Medicament m;
	int poz;
public:
	UndoSterge(MedicamentRepo& repo, const Medicament& m, int poz) : ActiuneUndo(), repo{ repo }, m{ m }, poz{ poz } {}

	void doUndo() override {
		repo.insertAt(m, poz);
	}
};

class UndoModifica : public ActiuneUndo {
private:
	MedicamentRepo& repo;
	Medicament m;
	int poz;
public:
	UndoModifica(MedicamentRepo& repo, const Medicament& m, int poz) : ActiuneUndo(), repo{ repo }, m{ m }, poz{ poz } {}

	void doUndo() override {
		repo.replace(poz, m);
	}
};