#pragma once
#include "../CeramicsMacro.h"
#include "IDataBuffer.h"
CERAMICS_NAMESPACE_BEGIN
template<class T>
class TArrayDataBuffer : public IDataBuffer
{
public:
    typedef TArrayDataBuffer type;
    TArrayDataBuffer(){}
    TArrayDataBuffer(T *data,size_t count)
    {
        this->reset(data,count);
    }
    TArrayDataBuffer(const type &other)
    {
        this->copy(other);
    }
    TArrayDataBuffer(type &&other)
    {
        this->swap(other);
    }
    virtual ~TArrayDataBuffer()
    {
        clear();
    }
    virtual size_t size()const
    {
        return mCount*sizeof(T);
    }
    virtual void *data()const
    {
        return mData;
    }
    size_t count()const
    {
        return mCount;
    }
    T *array()const
    {
        return mData;
    }
    type &reset(T *data, size_t count)
    {
        clear();
        mData = data;
        mCount = count;
    }
    type &insert(size_t pos,const T *source,size_t count)
    {
        do
        {
            if(pos<0||pos>mCount) break;
            if(source==nullptr || count <= 0) break;
            auto tmpData = new T[mCount+count];
            if(mData!=nullptr)
            {
                size_t last = mCount - pos;
                for(size_t i = 0 ; i < pos ; ++i )
                {
                    tmpData[i] = mData[i];
                }
                for(size_t i = pos ; i < pos + count ; ++i )
                {
                    tmpData[i] = source[i - pos];
                }
                for(size_t i = pos + count ; i <  last ; ++i )
                {
                    tmpData[i + pos + count ] = mData[i];
                }

                delete [] mData;
            }
            mData = tmpData;
            mCount += count;
        }while(0);
        return *this;
    }
    type &append(const T *source,size_t count)
    {
        return insert(mCount,source,count);
    }
    type &append(const type &source)
    {
        append(source.mData,source.mCount);
        return *this;
    }
    type &operator+(const type &source)
    {
        return this->append(source);
    }
    T &operator[](int idx) const
    {
        return mData[idx];
    }
    type &copy(const type &other)
    {
        clear();
        if(other.mData!=nullptr)
        {
            mData = new T[other.mCount];
            for(size_t i = 0 ; i < other.size;++i)
            {
                mData[i] = other.mDta[i];
            }
            mCount = other.mCount;
        }
        else
        {
            mData = other.mData;
            mCount = other.mCount;
        }
    }
    type &operator=(const type &other)
    {
        return this->copy(other);
    }
    type &swap(type &other)
    {
        auto tmpData = mData;
        auto tmpCount = mCount;
        mData = other.mData;
        mCount = other.mCount;
        other.mData = tmpData;
        other.mCount = tmpCount;
    }
    type &operator=(type &&other)
    {
        return this->swap(other);
    }
private:
    void clear()
    {
        if(mData!=nullptr)
        {
            delete [] mData;
            mData = nullptr;
            mCount = 0;
        }
    }
    size_t mCount = 0 ;
    T *mData=nullptr;
};
CERAMICS_NAMESPACE_END
