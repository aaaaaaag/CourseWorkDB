git submodule update --init --recursive

## Connect to postgres
sudo --login --user=postgres psql
\c mydb
\dt - show all tables
