#ifndef __PUBLIC_CLASS_H__
#define __PUBLIC_CLASS_H__

#define DELTE_COPY_CONSTRUCTION(className) className(className const &) = delete
#define DELTE_COPY_OPERATOR(className) className operator=(className const &) = delete

/**
 * @brief 禁止拷贝基类
 * 
 */
class DeleteCopyBase
{
public:
    DeleteCopyBase() = default;

    DELTE_COPY_CONSTRUCTION(DeleteCopyBase);
    DELTE_COPY_OPERATOR(DeleteCopyBase);
};

#endif