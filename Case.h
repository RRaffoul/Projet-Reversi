class Case {
 private:
	int pion; /*pourquoi rajouter un attribut position si liste de pointeurs dans le tableau ? */
 public:
	explicit Case(int valInit);
	int getPion() const;
	void setPion(int val);
};
