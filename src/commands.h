namespace commands {

class Visitor {
    public:
        virtual void visit(class Helper *) = 0;
        virtual void visit(class Creator *) = 0;
        virtual void visit(class Lister *) = 0;
        virtual void visit(class Deleter *) = 0;
};

class Visitable {
    public:
        virtual void accept(Visitor &v) = 0;
};

class Helper : public Visitable {
    public:
        Helper() {};
        void accept(Visitor &v) override;
};
class Creator : public Visitable {
    public:
        Creator() {};
        void accept(Visitor &v) override;
};
class Lister : public Visitable {
    public:
        Lister() {};
        void accept(Visitor &v) override;
};
class Deleter : public Visitable {
    public:
        Deleter() {};
        void accept(Visitor &v) override;
};

class Executor : public Visitor {
    public:
        void visit(Helper *) override;
        void visit(Creator *) override;
        void visit(Lister *) override;
        void visit(Deleter *) override;
};
// class Create
} // namespace commands