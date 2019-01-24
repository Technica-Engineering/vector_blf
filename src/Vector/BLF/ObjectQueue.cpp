/*
 * Copyright (C) 2013 Tobias Lorenz.
 * Contact: tobias.lorenz@gmx.net
 *
 * This file is part of Tobias Lorenz's Toolkit.
 *
 * Commercial License Usage
 * Licensees holding valid commercial licenses may use this file in
 * accordance with the commercial license agreement provided with the
 * Software or, alternatively, in accordance with the terms contained in
 * a written agreement between you and Tobias Lorenz.
 *
 * GNU General Public License 3.0 Usage
 * Alternatively, this file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU General Public License version 3.0 requirements will be
 * met: http://www.gnu.org/copyleft/gpl.html.
 */

#include <Vector/BLF/ObjectQueue.h>

#include <Vector/BLF/Exceptions.h>
#include <Vector/BLF/LogContainer.h>

namespace Vector {
namespace BLF {

template<typename T>
ObjectQueue<T>::ObjectQueue() :
    tellgChanged(),
    tellpChanged(),
    m_abort(false),
    m_queue(),
    m_tellg(0),
    m_tellp(0),
    m_bufferSize(0xffffffff),
    m_fileSize(0xffffffff),
    m_rdstate(std::ios_base::goodbit),
    m_mutex()
{
}

template<typename T>
ObjectQueue<T>::~ObjectQueue()
{
    abort();
}

template<typename T>
T * ObjectQueue<T>::read()
{
    /* mutex lock */
    std::unique_lock<std::mutex> lock(m_mutex);

    /* wait for data */
    tellpChanged.wait(lock, [this] {
        return
        m_abort ||
        !m_queue.empty() ||
        (m_tellg >= m_fileSize);
    });

    /* get first entry */
    T * ohb = nullptr;
    if (m_queue.empty()) {
        m_rdstate = std::ios_base::eofbit | std::ios_base::failbit;
    } else {
        ohb = m_queue.front();
        m_queue.pop();

        /* set state */
        m_rdstate = std::ios_base::goodbit;

        /* increase get count */
        m_tellg++;
    }

    /* notify */
    tellgChanged.notify_all();

    return ohb;
}

template<typename T>
DWORD ObjectQueue<T>::tellg() const
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_tellg;
}

template<typename T>
void ObjectQueue<T>::write(T * obj)
{
    /* mutex lock */
    std::unique_lock<std::mutex> lock(m_mutex);

    /* wait for free space */
    tellgChanged.wait(lock, [this] {
        return
        m_abort ||
        static_cast<DWORD>(m_queue.size()) < m_bufferSize;
    });

    /* push data */
    m_queue.push(obj);

    /* increase put count */
    m_tellp++;

    /* shift eof */
    if (m_tellp > m_fileSize) {
        m_fileSize = m_tellp;
    }

    /* notify */
    tellpChanged.notify_all();
}

template<typename T>
DWORD ObjectQueue<T>::tellp() const
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_tellp;
}

template<typename T>
bool ObjectQueue<T>::good() const
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return (m_rdstate == std::ios_base::goodbit);
}

template<typename T>
bool ObjectQueue<T>::eof() const
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return (m_rdstate & std::ios_base::eofbit);
}

template<typename T>
void ObjectQueue<T>::abort()
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* stop */
    m_abort = true;

    /* trigger blocked threads */
    tellgChanged.notify_all();
    tellpChanged.notify_all();
}

template<typename T>
void ObjectQueue<T>::setFileSize(DWORD fileSize)
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* set object count */
    m_fileSize = fileSize;

    /* notify */
    tellpChanged.notify_all();
}

template<typename T>
void ObjectQueue<T>::setBufferSize(DWORD bufferSize)
{
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* set max size */
    m_bufferSize = bufferSize;
}

template class ObjectQueue<ObjectHeaderBase>;

}
}
