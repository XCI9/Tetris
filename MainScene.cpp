template<typename Enumerator, class T, std::size_t Size>
class enumArray : public std::array<T, Size> {
public:
    T& operator[] (const Enumerator enumerator) {
        return std::array<T, Size>::operator[]((std::size_t)enumerator);
    }

    const T& operator[] (const Enumerator enumerator) const {
        return std::array<T, Size>::operator[]((std::size_t)enumerator);
    }
};

class Board : public QGraphicsScene{

};
