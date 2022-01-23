//部分实现
enum {_ALLGN = 8};  //小型区块的上调边界
enum {_MAX_BYTES = 128};
enum {_NFREELISTS = _MAX_BYTES/_ALLGN};  //free-lists个数

//以下是第二级配置器
template<bool threads , int inst>
class _default_alloc_template
{
    private:
        //ROUND_UP() 将bytes上调至８的倍数
        static size_t ROUND_UP(size_t bytes)
        {
            return (((bytes) + _ALLGN-1) & ~(_ALLGN-1)) ;
        }

        union obj
        {
                union obj * free_list_link;
                char clienr_data[1];
        };

        //16个free_lists
        static obj * volatile free_list[_NFREELISTS];
};