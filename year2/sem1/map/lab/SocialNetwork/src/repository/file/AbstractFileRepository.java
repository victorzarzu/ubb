package repository.file;

import domain.Entity;
import domain.User;
import repository.exceptions.ExistentEntityException;
import repository.exceptions.InexistentEntityException;
import repository.memory.InMemoryRepository;

import java.io.*;
import java.util.Arrays;
import java.util.List;

/**
 * Abstract class for a file repository
 */
public abstract class AbstractFileRepository<ID, E extends Entity<ID>> extends InMemoryRepository<ID, E> {
    private String filename;

    public AbstractFileRepository(String filename) {
        super();
        this.filename = filename;
        loadData();
    }

    /**
     * Method that loads data from file
     */
    private void loadData() {
        try(BufferedReader bufferedReader = new BufferedReader(new FileReader(this.filename))) {
            String line;
            while((line = bufferedReader.readLine()) != null) {
                List<String> atributes = Arrays.asList(line.split(";"));
                E entity = this.extractEntity(atributes);
                super.add(entity);
            }
        }
        catch (FileNotFoundException fileNotFoundException) {
            fileNotFoundException.printStackTrace();
        }
        catch (IOException ioException) {
            ioException.printStackTrace();
        }
    }

    private void saveData() {
        try(BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(this.filename))) {
            for(E entity : super.getAll()) {
                String entityString = this.entityEntityToString(entity);
                bufferedWriter.write(entityString);
            }
        } catch (FileNotFoundException fileNotFoundException) {
            fileNotFoundException.printStackTrace();
        } catch (IOException ioException) {
            ioException.printStackTrace();
        }
    }

    /**
     * Abstrct method that needs to extract entity from a list of atributes represented as String
     * @param atributes - the atributes of the returned entity
     * @return E
     */
    public abstract E extractEntity(List<String> atributes);

    /**
     * Method that converts the entity to a String
     * @param entity the entity to be converted to string
     * @return String - the entity in String format
     */
    protected abstract String entityEntityToString(E entity);

    /**
     * Method that adds an entity to the repo
     * @param entity E - the entity that needs to be added
     * @exception ExistentEntityException if the entity is already in the repo
     */
    @Override
    public void add(E entity) {
        super.add(entity);
        this.saveData();
    }

    /**
     * Method that removes an entity from repo
     * @param id ID - the id of the entity that needs to be removes
     * @exception IllegalArgumentException if id is null
     * @exception InexistentEntityException if there is no entity with the given id
     */
    @Override
    public void remove(ID id) {
        super.remove(id);
        this.saveData();
    }

    /**
     * Method that modifies an entity in the repo
     * @param entity entity that will replace the one with the same id
     * @exception IllegalArgumentException if id is null
     * @throws InexistentEntityException if there is no entity that has the same id as the given entity
     */
    public void modify(E entity) {
        super.modify(entity);
        this.saveData();
    }
}
