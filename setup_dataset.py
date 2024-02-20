import pandas as pd


def create_random_dataset():
    df = pd.read_csv('input/worldcities.csv', delimiter=',')
    last_two_columns = df.iloc[:, -2:]
    last_two_columns.to_csv('input/modified_file.csv', index=False)


if __name__ == "__main__":
    create_random_dataset()
