package com.ubb.repository;

import com.ubb.util.paging.Page;
import com.ubb.util.paging.Pageable;

import java.util.List;

public interface PagingRepository<E> extends Repository<E> {

    Page<E> findAllOnPage(Pageable pageable, List<E> elements);
}
