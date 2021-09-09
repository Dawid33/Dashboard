#!/bin/sh
if [[ -e test.db ]]; then
  rm test.db;
fi

sqlite3 test.db < test_db.sql