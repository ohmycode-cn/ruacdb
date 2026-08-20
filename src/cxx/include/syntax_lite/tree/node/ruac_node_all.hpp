/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/node/ruac_node_all.hpp
 *
 * @brief Aggregation header that includes all syntax node processor declarations.
 */

#pragma once
#ifndef RUAC_NODE_ALL_HPP
#define RUAC_NODE_ALL_HPP

#include "syntax_lite/tree/node/ruac_create_database.hpp" // IWYU pragma: keep
#include "syntax_lite/tree/node/ruac_create_table.hpp"    // IWYU pragma: keep
#include "syntax_lite/tree/node/ruac_show_databases.hpp"  // IWYU pragma: keep
#include "syntax_lite/tree/node/ruac_show_tables.hpp"     // IWYU pragma: keep
#include "syntax_lite/tree/node/ruac_use_database.hpp"    // IWYU pragma: keep

#endif // RUAC_NODE_ALL_HPP
