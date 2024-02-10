#include "byte_stream.hh"
#include <iostream>
using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ){}

bool Writer::is_closed() const
{
  // Your code here.
  return {closed_};
}

// VERSION 1
// void Writer::push( string data )
// {
//   // Your code here.
//   (void)data;
//   if(available_capacity()>=data.length())
//   {
//     byteBuffer+=data;
//     pushedByteNum += data.length();
//   }
//   else
//   {
//     // Writer.set_error();
//     int t = available_capacity();
//     byteBuffer+=data.substr(0,t);
//     // cerr<<"there is no more capacity to store data: "+data<<'\n';
//     // origin_capacity = 0;
//     pushedByteNum += t;
//     set_error();
//   }

//   return;
// }


void Writer::push( string data )
{
  // Your code here.
  int t = min(available_capacity(),data.length());
  
  pushedByteNum += t;
  byteBuffer+=data.substr(0,t);
  return;
}

void Writer::close()
{
  // Your code here.
  closed_ = true;
}

uint64_t Writer::available_capacity() const
{
  // Your code here.
  return {capacity_ - byteBuffer.length()};
}

uint64_t Writer::bytes_pushed() const
{
  // Your code here.
  return {pushedByteNum};
}

bool Reader::is_finished() const
{
  // Your code here.
  return finished_||(closed_&&pushedByteNum==popedByteNum);
}

uint64_t Reader::bytes_popped() const
{
  // Your code here.
  return {popedByteNum};
}

string_view Reader::peek() const
{
  // Your code here.
  return {byteBuffer};
}

void Reader::pop( uint64_t len )
{
  // Your code here.
  (void)len;

  len = min(byteBuffer.length(),len);
  // for(uint64_t i=0;i<len;i++)
  // {
  //   if(byteBuffer[i] == EOF)
  //   {
  //     len = i;
  //     finished_ = true;
  //     break;
  //   }
  // }
  byteBuffer = byteBuffer.substr(len);
  popedByteNum += len;
}

uint64_t Reader::bytes_buffered() const
{
  // Your code here.
  return {byteBuffer.length()};
}
