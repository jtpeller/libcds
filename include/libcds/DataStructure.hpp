// =================================================================
// DataStructure.hpp
//  Description     Declares the Data Structure Interfaces
//  Date            2025.07.02
//  Author          jtpeller
// =================================================================

#ifndef CDS_DATASTRUCTURE_HPP
#define CDS_DATASTRUCTURE_HPP

namespace CDS
{
    /**
     * IDataStructure -- Abstract Interface featuring all base level
     *  virtual methods to be overridden by higher-level structures
     */
    template <typename T>
    class IDataStructure
    {
    public:
        // constructor + destructor
        IDataStructure() {};
        virtual ~IDataStructure() {};

        // common utilities, getters, setters, etc.
        virtual bool Search(const T& value) = 0;
        virtual void Print() = 0;
        virtual bool Remove(const T& value) = 0;
        virtual void Clear() = 0;
        virtual size_t Size() = 0;
    };

    /**
     * IList -- Interface class for list-style data structures
     */
    template <typename T>
    class IList : IDataStructure<T>
    {
    private:
        // also track base class
        typedef IDataStructure BaseClass;

    public:
        // constructor + destructor
        IList() {};
        virtual ~IList() {};

        // IDataStructure members
        virtual bool Search(const T& value) override = 0;
        virtual void Print() override = 0;
        virtual bool Remove(const T& value) override = 0;
        virtual void Clear() override = 0;
        virtual size_t Size() override = 0;

        // IList members
        virtual size_t IndexOf(const T& value) = 0;
        virtual bool Insert(const T& value) = 0;
        virtual bool Insert(const T& value, size_t index) = 0;
        virtual T* Get(size_t index) = 0;
    };

    /**
     * ITree -- Interface class for tree-style data structures
     */
    template <typename T>
    class ITree : IDataStructure<T>
    {
    private:
        // track base class
        typedef IDataStructure BaseClass;

        // depth value
        size_t depth;

    public:
        // constructor + destructor
        ITree() {};
        virtual ~ITree() {};

        // TODO: ITree members
    };
} // namespace CDS

#endif
