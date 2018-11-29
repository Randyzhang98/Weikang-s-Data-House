#ifndef PLAYGROUND
#define PLAYGROUND



#include <vector>
// #include <unordered_map>
#include <queue>
#include <set>
#include <map>
#include <memory>
#include <string>


// using std::unordered_map;
using std::map;
using std::multimap;
using std::string;
using std::priority_queue;
using std::vector;
// using std::move;
using std::set;
using std::cout;
using std::endl;
using std::min;

class playground_t
{
    private:
        struct client_t
        {
            //typedef std::shared_ptr<client_t> Ptr;
            unsigned id;
            unsigned time_stamp;
            string name;
            string equity;
            unsigned price;
            unsigned quantity;
            int duration;
            client_t(unsigned id, unsigned time_stamp, string name, 
                    string equity, unsigned price, unsigned quantity, int duration): 
                    id(id), time_stamp(time_stamp), name((name)), equity((equity)), 
                    price(price), quantity(quantity), duration(duration) {}
        };

        struct smaller_t // this part need much more concern 
        {
            bool operator() (const client_t &a, const client_t &b) const
            {
                if (a.price == b.price)
                {
                    return a.id > b.id;
                }
                else return a.price > b.price;
            }
        };

        struct greater_t
        {
            bool operator() (const client_t &a, const client_t &b) const
            {
                if (a.price == b.price)
                {
                    return a.id > b.id;
                }
                else return a.price < b.price;
            }
        };  

        struct trader_t
        {
            priority_queue <client_t, vector<client_t>, greater_t> buyers;
            priority_queue <client_t, vector<client_t>, smaller_t> sellers;
        };

        struct price_median_t
        {
            unsigned number_of_elements;
            price_median_t(): number_of_elements(0) {}
            // L12 P39 median maintainese
            priority_queue <unsigned, vector<unsigned>, std::greater<unsigned> > max_heap;
            priority_queue <unsigned, vector<unsigned>, std::less<unsigned> > min_heap;
            void insert(unsigned in)
            {
                if ( number_of_elements % 2 == 1 )
                {
                    if ( in >= max_heap.top() ) min_heap.push(in);
                    else 
                    {
                        unsigned temp = max_heap.top();
                        min_heap.push(temp);
                        max_heap.pop();
                        max_heap.push(in);
                    }
                }
                else 
                {
                    if ( number_of_elements == 0 || in <= min_heap.top()) max_heap.push(in);
                    else 
                    {
                        unsigned temp = min_heap.top();
                        max_heap.push(temp);
                        min_heap.pop();
                        min_heap.push(in);
                    }
                }
                number_of_elements ++ ;
            }   
            unsigned getMedian() const 
            {
                if (number_of_elements % 2 == 1 ) 
                {
                    return max_heap.top();
                }
                else if (number_of_elements == 0)
                {
                    return -1; // indicate no trade has been made;
                }
                else 
                {
                    return (max_heap.top() + min_heap.top() ) / 2; 
                }
            }
        };

        struct transfer_holder_t
        {
            unsigned num_sold, num_bought;
            int net_income;
            transfer_holder_t() : num_sold(0), num_bought(0), net_income(0) {}
        };

        // struct tttGoods
        // {
        //     bool 
        // }

        struct ttt_holder_t
        {
            unsigned id, price;
            //int duration;
            unsigned time_stamp;
            bool trader_is_buyer;
            ttt_holder_t(unsigned id, unsigned price, unsigned time_stamp, bool trader_is_buyer ): id(id), price(price), time_stamp(time_stamp), trader_is_buyer(trader_is_buyer) {} 
        };
        struct ttt_holder_list_t
        {
            vector<ttt_holder_t> traders;
        };

        map<string, trader_t> traders_in_goods;

        set<string> equity_list; //goods name

        map<string, transfer_holder_t> transfers_info_list;

        map<string, price_median_t> price_median_list; // goods name first;

        //ttt part remains to be filled.

        map<string,ttt_holder_list_t> ttt_list;

        bool verbose_flag = false;
        bool median_flag = false;
        bool midpoint_flag = false;
        bool transfers_flag = false;
        bool ttt_flag = false;

        unsigned playground_income = 0, overall_money_tranfered = 0, num_completed_trade = 0, num_shared_equity = 0;

        void transfersPrint()
        {
            for (auto & temp : transfers_info_list)
            {
                cout << temp.first << " bought " << temp.second.num_bought << " and sold " << temp.second.num_sold << " for a net transfer of $" << temp.second.net_income << endl;
            }
        }
        
  
        playground_t() = default;
    public:
        unsigned current_time_stamp = 0;
        //playground_t() = default;
        ~playground_t() = default;
        //playground_t &operator;
        //some default operation remains to be deleted;

        void ttt_holder_adder (string input)
        {
            // cout << 111 << endl;
            ttt_holder_list_t ept_ttt;
            ttt_list[input] = ept_ttt;
        }

        static playground_t & getInstance()
        {
            static playground_t playground;
            return playground;
        }

        void setFlag(const bool &v_flag, const bool &m_flag, const bool &mid_flag, const bool &tran_flag, const bool &t_flag)
        {
            verbose_flag = v_flag;
            median_flag = m_flag;
            midpoint_flag = mid_flag;
            transfers_flag = tran_flag;
            ttt_flag = t_flag;
        }
        
        void buyerPart (unsigned id, unsigned time_stamp, string name, string equity, unsigned price, unsigned number_of_elements, int duration)
        {
            if (ttt_flag) 
            {   
                if (ttt_list.find(equity) != ttt_list.end() )
                {
                    ttt_holder_t in(id, price, time_stamp, true);
                    ttt_list[equity].traders.emplace_back(in);
                }
               
            }
            if(midpoint_flag) 
            {
                if (equity_list.find(equity) == equity_list.end())
                {
                    equity_list.insert(equity);
                }
            }
            
            // auto iter = traders_in_goods.find(equity);
            // if (iter == traders_in_goods.end())
            // {
            //     traders_in_goods
            // }

            trader_t & this_field = traders_in_goods[equity];

            while (!this_field.sellers.empty() && number_of_elements > 0)
            {
                const client_t & temp = this_field.sellers.top();
                if ( temp.duration > 0 && current_time_stamp >= temp.duration + temp.time_stamp)
                {
                    this_field.sellers.pop();
                    continue;
                }
                if ( temp.price > price) break; // the price the buyer order is too low to fit

                //this is the trading part
                unsigned num_dealt_goods = min(number_of_elements, temp.quantity);
                //this part is the main bottleneck of performance, need ptr.
                unsigned transfered_money = num_dealt_goods * temp.price; // seller decieded the price in final
                unsigned trading_fees = transfered_money / 100;
                unsigned finished_price = temp.price;// seller decieded the price in final

                client_t insert_item = temp;
                
                insert_item.quantity -= num_dealt_goods;
                number_of_elements -= num_dealt_goods;
                playground_income += 2 * trading_fees;
                overall_money_tranfered += transfered_money;
                num_completed_trade ++;
                num_shared_equity += num_dealt_goods;

                

                if (verbose_flag) 
                {
                    cout << name << " purchased " << num_dealt_goods << " shares of " << equity << " from " << temp.name << " for $" << finished_price << "/share" << endl; 
                }
                if (median_flag)
                {
                    price_median_list[equity].insert(finished_price);
                }
                if (transfers_flag)
                {
                    transfers_info_list[name].num_bought += num_dealt_goods;
                    transfers_info_list[name].net_income -= transfered_money;
                    transfers_info_list[temp.name].num_sold += num_dealt_goods;
                    transfers_info_list[temp.name].net_income += transfered_money;
                }


                this_field.sellers.pop(); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                if (insert_item.quantity > 0)  this_field.sellers.emplace(insert_item);
            }
            if (number_of_elements > 0 && duration != 0)
            {
                client_t input( id, time_stamp, name, equity, price, number_of_elements, duration );
                this_field.buyers.emplace( input);
            }

        }

        void sellerPart (unsigned id, unsigned time_stamp, string name, string equity, unsigned price, unsigned number_of_elements, int duration)
        {
            if (ttt_flag) 
            {   
                if (ttt_list.find(equity) != ttt_list.end() )
                {
                    ttt_holder_t in(id, price, time_stamp, false);
                    ttt_list[equity].traders.emplace_back(in);
                }
                
            }
            if(midpoint_flag) 
            {
                if (equity_list.find(equity) == equity_list.end())
                {
                    equity_list.insert(equity);
                }
            }
          
            // auto iter = traders_in_goods.find(equity);
            // if (iter == traders_in_goods.end())
            // {
            //     traders_in_goods
            // }

            trader_t & this_field = traders_in_goods[equity];

            while (!this_field.buyers.empty() && number_of_elements > 0)
            {
                const client_t & temp = this_field.buyers.top();
                if ( temp.duration > 0 && (current_time_stamp >= temp.duration + temp.time_stamp) )
                {
                    this_field.buyers.pop();
                    continue;
                }
                if ( temp.price < price) break; // the price the buyer order is too low to fit

                //this is the trading part
                unsigned num_dealt_goods = min(number_of_elements, temp.quantity);
                //this part is the main bottleneck of performance, need ptr.
                unsigned transfered_money = num_dealt_goods * temp.price; // buyer decieded the price in final
                unsigned trading_fees = transfered_money / 100;
                unsigned finished_price = temp.price;// buyer decieded the price in final

                client_t insert_item = temp;
                
                insert_item.quantity -= num_dealt_goods;
                number_of_elements -= num_dealt_goods;

                playground_income += 2 * trading_fees;
                overall_money_tranfered += transfered_money;
                num_completed_trade ++;
                num_shared_equity += num_dealt_goods;

                

                if (verbose_flag) 
                {
                    cout << temp.name << " purchased " << num_dealt_goods << " shares of " << equity << " from " << name << " for $" << finished_price << "/share" << endl; 
                }
                if (median_flag)
                {
                    price_median_list[equity].insert(finished_price);
                }
                if (transfers_flag)
                {
                    transfers_info_list[name].num_sold += num_dealt_goods;
                    transfers_info_list[name].net_income += transfered_money;
                    transfers_info_list[temp.name].num_bought += num_dealt_goods;
                    transfers_info_list[temp.name].net_income -= transfered_money;
                }


                this_field.buyers.pop(); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                if (insert_item.quantity > 0)  this_field.buyers.emplace(insert_item);
            }
            if (number_of_elements > 0 && duration != 0)
            {
                client_t input( id, time_stamp, name, equity, price, number_of_elements, duration );
                this_field.sellers.emplace( input);
            }

        }

        void medianPrint() const
        {
            for (auto &item : price_median_list)
            {
                cout << "Median match price of " << item.first << " at time " << current_time_stamp << " is $" << item.second.getMedian() << '\n';
            }
        }

        void midpointPrint()
        {
            for (auto &item : equity_list)
            {
                auto &buyer = traders_in_goods[item].buyers;
                auto &seller = traders_in_goods[item].sellers;
                while (!buyer.empty() && buyer.top().duration > 0 && ( current_time_stamp >= buyer.top().duration + buyer.top().id)  )
                {
                    buyer.pop();
                }
                while (!seller.empty() && seller.top().duration > 0 && ( current_time_stamp >= seller.top().duration + seller.top().id)  )
                {
                    seller.pop();
                }

                cout << "Midpoint of " << item << " at time " << current_time_stamp << " is ";
                if (buyer.empty() || seller.empty())
                {
                    cout << "undefined " << endl;
                }
                else 
                {
                    cout << "$" << ( (buyer.top().price + seller.top().price) / 2 ) << endl;
                }
            }
        }

        void plot_simple_trader_holder(const ttt_holder_t & it)
        {
            cout << "The ttt_holder_t is ";
            cout << "of id:" << it.id;
            cout << " of time_stamp:" << it.time_stamp;
            cout << " is a buyer:" << it.trader_is_buyer << endl;
        }

        void stagement()
        {
            string line;        
            stringstream line_buffer;
            unsigned id = 0;
            while (getline(cin, line) && !line.empty() ) // could be replaced by while(!cin.eof())
            {
                char special_char;
                string name, op, equity;
                int duration;
                unsigned time_stamp, price, number_of_elements;
                line_buffer << line;
                line_buffer >> time_stamp >> name >> op >> equity >> special_char >> price >> special_char >> number_of_elements >> duration;
                line_buffer.clear();

                if (time_stamp > this->current_time_stamp) 
                {
                    if (median_flag) this->medianPrint(); 
                    if (midpoint_flag) this->midpointPrint();   //laster round trading summary
                    this->current_time_stamp = time_stamp;
                }

                if (op == "BUY")
                {
                    this->buyerPart(id, time_stamp, name, equity, price, number_of_elements, duration);
                }
                else 
                {
                    this->sellerPart ( id, time_stamp, name, equity, price, number_of_elements, duration );
                }
                id++;
            }
            if (median_flag) this->medianPrint();
            if (midpoint_flag) this->midpointPrint();
        }

        void conclusion() 
        {
            cout << "---End of Day---" << endl;
            cout << "Commission Earnings: $" << playground_income << endl;;
            cout << "Total Amount of Money Transferred: $" << overall_money_tranfered << endl;
            cout << "Number of Completed Trades: " << num_completed_trade << endl;
            cout << "Number of Shares Traded: " << num_shared_equity << endl;
            if (transfers_flag)
            {
                for (auto & item : transfers_info_list)
                {
                    cout << item.first << " bought " << item.second.num_bought << " and sold " << item.second.num_sold << " for a net transfer of $" << item.second.net_income << endl;
                }
            }
            if (ttt_flag)
            {
                cout << "tt_list's length is " << ttt_list.size() << endl;
                for (auto iter = ttt_list.begin(); iter != ttt_list.end(); iter++)
                {
                    vector<ttt_holder_t> & all_traders = iter->second.traders;
                    string equity_name = iter->first;
                    bool matched_flag = false;
                    bool seller_exist = false;
                    int difference_of_price = -10700000;
                    int seller_claim_price = 107000000;
                    unsigned time_stamp_1 = -1, time_stamp_2 = -1;
                    
                    plot_simple_trader_holder (all_traders[1]);

                    for (auto & it : all_traders)
                    {
                        if (it.trader_is_buyer == false) // this is seller's claim price stage;
                        {
                            seller_exist = true;
                            if (it.price < seller_claim_price)
                            {
                                time_stamp_1 = it.time_stamp;
                                seller_claim_price = it.price;
                            }
                        }
                        else // buyer
                        {
                            if (seller_exist) matched_flag = true;
                            if ( matched_flag && (signed)(it.price - seller_claim_price) > difference_of_price )
                            {
                                time_stamp_2 = it.time_stamp;
                                difference_of_price = it.price - seller_claim_price;
                            }
                        }
                    }
                    cout << "Time travelers would buy " << equity_name << " at time: " << time_stamp_1 << " and sell it at time: " << time_stamp_2 << '\n';
                }
            }
        }









};




#endif

